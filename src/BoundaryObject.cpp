#include <QtCore/QVector>
#include <QVector3D>
#include "BoundaryObject.h"

BoundaryObject::BoundaryObject(string s, float data) : Object(data) {
    readObj(s);
}

BoundaryObject::BoundaryObject(const QString &fileName, float data) : Object(data) {
    QFile file(fileName);
    if (file.exists()) {
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QVector<QVector3D> v;

            while (!file.atEnd()) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if (lineParts.count() > 0) {
                    // if it’s a comment
                    if (lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0) {
                        // qDebug() << line.remove(0, 1).trimmed();
                    }

                        // if it’s a vertex position (v)
                    else if (lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0) {
                        vertexs.push_back(vec4(lineParts.at(1).toFloat(),
                                               lineParts.at(2).toFloat(),
                                               lineParts.at(3).toFloat(), 1.0f));
                    }

                        // if it’s a normal (vn)
                    else if (lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0) {

                    }
                        // if it’s a texture (vt)
                    else if (lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0) {

                    }

                        // if it’s face data (f)
                        // there’s an assumption here that faces are all triangles
                    else if (lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0) {
                        Cara *cara = new Cara();

                        // get points from v array
                        cara->idxVertices.push_back(lineParts.at(1).split("/").at(0).toInt() - 1);
                        cara->idxVertices.push_back(lineParts.at(2).split("/").at(0).toInt() - 1);
                        cara->idxVertices.push_back(lineParts.at(3).split("/").at(0).toInt() - 1);

                        //Calcula normal
                        cara->calculaNormal(vertexs);
                        //Afegeix cara
                        cares.push_back(*cara);


                    }

                }
            }
            file.close();
        }
    }
}


BoundaryObject::~BoundaryObject() {

}

bool BoundaryObject::intersection(const Ray &raig, float t_min, float t_max, IntersectionInfo &info) const {
    IntersectionInfo interAux;
    bool intersected = false;
    float closest_t_to_observer = FLT_MAX;
    for (Cara cara : cares) {
        if (cara.intersection(raig, t_min, t_max, interAux, this->vertexs, getConstMaterial())) {
            intersected = true;
            if (interAux.t < closest_t_to_observer) {
                closest_t_to_observer = interAux.t;
                info = interAux;
            }
        }
    }
    return intersected;
}

// Llegeix un fitxer .obj
//  Si el fitxer referencia fitxers de materials (.mtl), encara no es llegeixen
//  Tots els elements del fitxer es llegeixen com a un unic objecte.
void BoundaryObject::readObj(string filename) {

    FILE *fp = fopen(filename.c_str(), "rb");
    if (!fp) {
        cout << "No puc obrir el fitxer " << endl;
    } else {

        while (true) {
            char *comment_ptr = ReadFile::fetch_line(fp);

            if (comment_ptr == (char *) -1)  /* end-of-file */
                break;

            /* did we get a comment? */
            if (comment_ptr) {
                //make_comment (comment_ptr);
                continue;
            }

            /* if we get here, the line was not a comment */
            int nwords = ReadFile::fetch_words();

            /* skip empty lines */
            if (nwords == 0)
                continue;

            char *first_word = ReadFile::words[0];

            if (!strcmp(first_word, "v")) {
                if (nwords < 4) {
                    fprintf(stderr, "Too few coordinates: '%s'", ReadFile::str_orig);
                    exit(-1);
                }

                string sx(ReadFile::words[1]);
                string sy(ReadFile::words[2]);
                string sz(ReadFile::words[3]);
                double x = atof(sx.c_str());
                double y = atof(sy.c_str());
                double z = atof(sz.c_str());

                if (nwords == 5) {
                    string sw(ReadFile::words[4]);
                    double w = atof(sw.c_str());
                    x /= w;
                    y /= w;
                    z /= w;
                }
                // S'afegeix el vertex a l'objecte
                vertexs.push_back(vec4(x, y, z, 1));

            } else if (!strcmp(first_word, "vn")) {
            } else if (!strcmp(first_word, "vt")) {
            } else if (!strcmp(first_word, "f")) {
                // S'afegeix la cara a l'objecte
                // A modificar si es vol carregar mes de un objecte
                construeix_cara(&ReadFile::words[1], nwords - 1, this, 0);
            }
                // added
            else if (!strcmp(first_word, "mtllib")) {
                //read_mtllib (&words[1], nwords-1, matlib, filename);
            } else if (!strcmp(first_word, "usemtl")) {
                //int size = strlen(words[1])-1;
                //while (size && (words[1][size]=='\n' || words[1][size]=='\r') ) words[1][size--]=0;
                //currentMaterial = matlib.index(words[1]);
            }
                // fadded
            else {
                //fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
            }
        }
    }
    fclose(fp);
}

/**
 * @brief BoundaryObject::construeix_cara
 * @param words
 * @param nwords
 * @param objActual
 * @param vindexUlt
 */
void BoundaryObject::construeix_cara(char **words, int nwords, BoundaryObject *objActual, int vindexUlt) {
    Cara face;

    for (int i = 0; i < nwords; i++) {
        int vindex;
        int nindex;
        int tindex;

        if ((words[i][0] >= '0') && (words[i][0] <= '9')) {
            ReadFile::get_indices(words[i], &vindex, &tindex, &nindex);

#if 0
            printf ("vtn: %d %d %d\n", vindex, tindex, nindex);
#endif

            /* store the vertex index */

            if (vindex > 0)       /* indices are from one, not zero */
                face.idxVertices.push_back(vindex - 1 - vindexUlt);
            else if (vindex < 0)  /* negative indices mean count backwards */
                face.idxVertices.push_back(objActual->vertexs.size() + vindex);
            else {
                fprintf(stderr, "Zero indices not allowed: '%s'\n", ReadFile::str_orig);
                exit(-1);
            }
        }
    }
    face.color = vec4(1.0, 0.0, 0.0, 1.0);
    objActual->cares.push_back(face);
}

void BoundaryObject::aplicaTG(TG *t) {
    int n = vertexs.size();
    mat4 tg = t->getTG();
    for(int i = 0; i < n; i++){
        vertexs[i] = tg*vertexs[i];
    }
}

vec3 BoundaryObject::getObjectCenter(){
    vec3 c(0,0,0);
    for(vec4 v: vertexs){
        c.x += v.x;
        c.y += v.y;
        c.z += v.z;
    }
    return c/(float)vertexs.size();
}
