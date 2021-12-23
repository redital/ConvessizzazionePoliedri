#include "ConcaveToConvex.hpp"

#include "geometryUnitTest.hpp"
#include "Eigen"
#include "Output.hpp"

#include "Polygon.hpp"
#include "Polyhedron.hpp"
#include "ConcaveToConvex.hpp"
#include "Intersector2D1D.hpp"
#include "Intersector1D1D.hpp"
#include "Intersector2D2D.hpp"



using namespace std;
using namespace MainApplication;

namespace GeDiM
{
  // ***************************************************************************
  bool ConcaveToConvex::IsPolygonConvex(const IPolygon& polygon, const double& tolerance)
  {
    return false;
  }
  // ***************************************************************************
  Output::ExitCodes ConcaveToConvex::ConcaveToConvexPolygon(const IPolygon& concavePolygon, list<IPolygon*>& convexPolygons, const double& tolerance)
  {
    convexPolygons.push_back(concavePolygon.Clone());

    return Output::UnimplementedMethod;
  }
  // ***************************************************************************
  bool ConcaveToConvex::IsPolyhedronConvex(const IPolyhedron& polyhedron, const double& tolerance, vector<int*>& problemi)
  {
    unsigned int i=0,j=0;
    bool flag=1;
    string messaggio;



    ///stampa numero di facce
    /*
    if (polyhedron.NumberOfFaces()==0){
        messaggio="VUOTO ";
    }
    else{
        stringstream sf,sv,ss;
        sf << polyhedron.NumberOfFaces();
        messaggio="Il poliedro ha " + sf.str() +" facce.";
        ss << polyhedron.NumberOfSegments();
        messaggio=messaggio + " Il poliedro ha " + ss.str() +" segmenti.";
        sv << polyhedron.NumberOfVertices();
        messaggio=messaggio + " Il poliedro ha " + sv.str() +" vertici.";
    }
    cout<<messaggio<<endl;

    */
    ///vettore con le coordinate dei vertici
    const vector<const Vertex*>& coordinate = polyhedron.Vertices();


    ///stampa delle coordinate dei vertici
    /*for (j=0;j<polyhedron.NumberOfVertices();j++){
        cout<<"vertice n "<<j+1<<" "<<endl<<*coordinate[j]<<endl;
    }*/



    ///effettivo controllo
    for (i=0;i<polyhedron.NumberOfFaces();i++){
        int uguali=0, occorrenze=0;
        const IPolygon& faccia = polyhedron.GetFace(i);//acquisizione iesima faccia

        ///stampa PlaneNormal e PlaneTranslation della faccia
        //cout<<endl<<"Faccia n "<<i+1<<endl<<*faccia.GetPlaneNormal()<<endl<<faccia.GetPlaneTranslation()<<endl<<endl;

        Vector3d componenti = *faccia.GetPlaneNormal();//copia dei coefficenti del piano per più agile utilizzo
        for (j=0;j<polyhedron.NumberOfVertices();j++){
            Vector3d coordinate_vertice = *coordinate[j];//copia delle coordinate dei vertici per più agile utilizzo
            //cout<<"vertice n "<<j+1<<endl;
            ///controllo appartenenza vertice alla faccia
            if (componenti[0]*coordinate_vertice[0]+componenti[1]*coordinate_vertice[1]+componenti[2]*coordinate_vertice[2] > faccia.GetPlaneTranslation()- tolerance && componenti[0]*coordinate_vertice[0]+componenti[1]*coordinate_vertice[1]+componenti[2]*coordinate_vertice[2] < faccia.GetPlaneTranslation() + tolerance){
               uguali++;//conteggio vertici della faccia
            }
            ///controllo posizione di un vertice non appartenente alla faccia rispetto alla faccia stessa
            else {
                if (componenti[0]*coordinate_vertice[0]+componenti[1]*coordinate_vertice[1]+componenti[2]*coordinate_vertice[2] > faccia.GetPlaneTranslation()){
                    occorrenze++;
                }
                else{
                    occorrenze--;
                }
            }
        }
        ///controllo se è convesso
        if (!(polyhedron.NumberOfVertices()==(uguali+abs(occorrenze)))){
            flag=0;
            problemi.push_back(new int);
            vector<int*>::iterator it=problemi.end();
            it--;
            **it=i;
        }
    }

    /*cout<<endl<<"Problemi sulle facce: ";
    for(vector<int*>::iterator iter1=problemi.begin();iter1!=problemi.end();iter1++){
        cout<<**iter1+1<<", ";
    }
    cout<<endl;
    */
    return flag;
  }
  // ***************************************************************************
  Output::ExitCodes ConcaveToConvex::ConcaveToConvexPolyhedron(IPolyhedron& concavePolyhedron, list<IPolyhedron*>& convexPolyhedra, const double& tolerance,vector<int*>& problemi)
  {

    bool uscita=0;

    ///scorro le facce problematiche
    for (vector<int*>::iterator iter1=problemi.begin();iter1!=problemi.end() && uscita==0;iter1++){
        if(iter1!=problemi.begin()){
            iter1--;
            problemi.erase(iter1);
           }
        for (vector<int*>::iterator iter2=problemi.begin();iter2!=problemi.end() && uscita==0;iter2++){
            ///salto i controlli tra facce problematiche uguali
            if (iter1!=iter2){
                ///definizione facce per il confronto
                const IPolygon& faccia1 = concavePolyhedron.GetFace(**iter1);
                const IPolygon& faccia2 = concavePolyhedron.GetFace(**iter2);
                ///scorro i segmenti per cercare quello in comune (ricordati di aggiustare la questione dulicati)
                for (unsigned int i=0;i<faccia1.NumberOfSegments();i++){
                    for (unsigned int j=0;j<faccia2.NumberOfSegments();j++){
                        if (&faccia1.GetSegment(i) == &faccia2.GetSegment(j)){
                                ///prendo il segmento in comune
                                const ISegment *segmento=&faccia1.GetSegment(i);

                                ///creo la faccia di taglio

                                /// dobbiamo recuperare i due vertici del segmento preso, un vertice che non appartiene alle
                                /// facce problematiche e costruire una faccia con questi 3 punti.
                                IPolygon* face = new Polygon;

                                ///aggiungo i vertici di inizio e fine
                                face->AddVertex(segmento->Origin());
                                face->AddVertex(segmento->End());

                                ///cerco un vertice non appartenenter alle facce problematiche
                                Vertex vertice;
                                bool trovato=0;
                                for (unsigned int k=0;k<concavePolyhedron.NumberOfVertices() && trovato==0;k++){
                                    vertice=concavePolyhedron.GetVertex(k);
                                    ///se il vertice appartiene ad una faccia problemnatica il flag va a 1
                                    bool flag=0;
                                    for (unsigned int n=0; n<faccia1.NumberOfVertices() && flag==0; n++){
                                        if (vertice == faccia1.GetVertex(n)){
                                            flag=1;
                                        }
                                    }
                                    for (unsigned int n=0; n<faccia2.NumberOfVertices() && flag==0; n++){
                                        if (vertice == faccia2.GetVertex(n)){
                                            flag=1;
                                        }
                                    }
                                    ///se il flag rimane 0 abbiamo trovato il nostro vertice e non serve più ciclare
                                    if (flag==0){
                                        trovato=1;

                                    }
                                }
                                ///aggiungo i il vertice trovato, il segmento di separazione delle facce problematiche e i
                                ///segmenti che uniscono il vertice trovato con il segmento
                                Segment seg1;
                                Segment seg2;
                                face->AddVertex(vertice);
                                face->AddSegment(*segmento);

                                seg1.Initialize(vertice, segmento->Origin());
                                face->AddSegment(seg1);
                                seg2.Initialize(vertice, segmento->End());
                                face->AddSegment(seg2);
                                //aggiunti altri due segmenti

                                ///computo vari fatti
                                face->ComputePlane();
                                face->ComputeCentroid();
                                face->ComputeRotatedVertices();


                                ///eliminiamo i vertici della faccia di taglio e mettiamo al loro posto quelli
                                ///che calcoliamo dall'intersezione della faccia di taglio con i segmenti

                                Vector3d componenti = *face->GetPlaneNormal();
                                face->DeleteVertices();
                                for(unsigned int e =0;e<concavePolyhedron.NumberOfSegments();e++){
                                    Vector3d origine = concavePolyhedron.GetSegment(e).Origin();
                                    Vector3d fine = concavePolyhedron.GetSegment(e).End();

                                    ///verifichiamo la posizione rispetto alla faccia di taglio dell'origine e della fine del segmento in esame
                                    ///definiamo un lato arbitrario positivo con 1. -1 sarà dall'altro lato
                                    int segno_origine = 0;
                                    int segno_fine = 0;
                                    if (componenti[0]*origine[0]+componenti[1]*origine[1]+componenti[2]*origine[2] > face->GetPlaneTranslation()+tolerance){
                                        segno_origine=1;
                                    }
                                    else{
                                        if (componenti[0]*origine[0]+componenti[1]*origine[1]+componenti[2]*origine[2] < face->GetPlaneTranslation()-tolerance){
                                            segno_origine=-1;
                                        }
                                        else{
                                            segno_origine=0;
                                        }
                                    }
                                    if (componenti[0]*fine[0]+componenti[1]*fine[1]+componenti[2]*fine[2] > face->GetPlaneTranslation()+tolerance){
                                        segno_fine=1;
                                    }
                                    else{
                                        if (componenti[0]*fine[0]+componenti[1]*fine[1]+componenti[2]*fine[2] < face->GetPlaneTranslation()-tolerance){
                                            segno_fine=-1;
                                        }
                                        else{
                                            segno_fine=0;
                                        }
                                    }

                                    ///intersechiamo solo quelli che hanno i vertici separati oppure uno appartenente per evitare intersezioni esterne al poliedro
                                    if(segno_fine*segno_origine<=0){//i segni sono discordi e i vertici sono separati o uno dei due appartiene alla faccia
                                        Intersector2D1D intersezione_in_corso;
                                        intersezione_in_corso.SetPlane(*face->GetPlaneNormal(),face->GetPlaneTranslation());

                                        intersezione_in_corso.SetLine(concavePolyhedron.GetSegment(e).Origin(), concavePolyhedron.GetSegment(e).Tangent());
                                        intersezione_in_corso.ComputeIntersection();
                                        Vertex* punto_intersezione = new Vertex;
                                        *punto_intersezione=intersezione_in_corso.IntersectionPoint();
                                        //Calcolato punto intersezione, adesso controllo che non sia un duplicato
                                        bool vessillo=0;
                                        for (unsigned int d=0; d<face->NumberOfVertices() && vessillo==0; d++){
                                            if((intersezione_in_corso.IntersectionPoint()[0] - face->GetVertex(d)[0])*(intersezione_in_corso.IntersectionPoint()[0] - face->GetVertex(d)[0]) + (intersezione_in_corso.IntersectionPoint()[1] - face->GetVertex(d)[1])*(intersezione_in_corso.IntersectionPoint()[1] - face->GetVertex(d)[1]) + (intersezione_in_corso.IntersectionPoint()[2] - face->GetVertex(d)[2])*(intersezione_in_corso.IntersectionPoint()[2] - face->GetVertex(d)[2]) <= tolerance*tolerance){
                                                vessillo=1;
                                            }
                                        }
                                        if (!vessillo && !(intersezione_in_corso.IsCoplanar()) ){
                                            face->AddVertex(*punto_intersezione);
                                            //intersezione aggiunta alla faccia di taglio
                                        }
                                        if(segno_fine*segno_origine<0){ //i segni sono discordi e i vertici sono separati
                                            ///tagliamo il segmento che congiunge i due vertici separati in due segmenti
                                            ///che hanno in comune il punto di intersezione
                                            concavePolyhedron.AddVertex(*punto_intersezione);
                                            concavePolyhedron.RemoveSegment(e);
                                            Segment segmento_sinistro;
                                            Segment segmento_destro;
                                            segmento_sinistro.Initialize(concavePolyhedron.GetSegment(e).Origin(),*punto_intersezione);
                                            segmento_destro.Initialize(*punto_intersezione,concavePolyhedron.GetSegment(e).End());
                                            segmento_destro.ComputeTangent();
                                            segmento_sinistro.ComputeTangent();
                                            concavePolyhedron.AddSegment(segmento_sinistro);
                                            concavePolyhedron.AddSegment(segmento_destro);
                                        }
                                    }
                                }
                                //ho calcolato i nuovi vertici

                                ///eliminiamo tutti i segmenti della faccia di taglio e li sostiuiamo con quelli ottenuti
                                ///collegando tra di loro i vertici appena ottenuti che appartengono alla medesima faccia del poliedro iniziale
                                face->DeleteSegments();
                                for(unsigned int e=0;e<concavePolyhedron.NumberOfFaces();e++){///prendo una faccia
                                    componenti=*concavePolyhedron.GetFace(e).GetPlaneNormal();
                                    for (unsigned int f=0;f<face->NumberOfVertices();f++){///cerco un vertice che appartiene alla faccia
                                        Vertex vertice_da_controllare=face->GetVertex(f);
                                        if (componenti.dot(vertice_da_controllare)<concavePolyhedron.GetFace(e).GetPlaneTranslation()+tolerance
                                            && componenti.dot(vertice_da_controllare)>concavePolyhedron.GetFace(e).GetPlaneTranslation()-tolerance){
                                            Vertex vertice_trovato1=vertice_da_controllare;
                                            vector <Segment*> vettseg;
                                            int indice=0;
                                            for (unsigned int d=0; d<face->NumberOfVertices();d++){///cerco un secondo vertice che appartiene alla faccia
                                                vertice_da_controllare=face->GetVertex(d);
                                                if (componenti.dot(vertice_da_controllare)<concavePolyhedron.GetFace(e).GetPlaneTranslation()+tolerance
                                                    && componenti.dot(vertice_da_controllare)>concavePolyhedron.GetFace(e).GetPlaneTranslation()-tolerance
                                                    && vertice_da_controllare!=vertice_trovato1){

                                                    Segment segmento_da_aggiungere;///creo il segmento
                                                    segmento_da_aggiungere.Initialize(vertice_trovato1, vertice_da_controllare);

                                                    bool vessicchio=0;///controllo di non averlo aggiunto in precedenza
                                                    for (unsigned int g=0; g<face->NumberOfSegments() && vessicchio==0; g++){
                                                        if ((face->GetSegment(g).Origin()==segmento_da_aggiungere.Origin() && face->GetSegment(g).End()==segmento_da_aggiungere.End()) || (face->GetSegment(g).Origin()==segmento_da_aggiungere.End() && face->GetSegment(g).End()==segmento_da_aggiungere.Origin() )){
                                                            vessicchio=1;
                                                        }
                                                    }
                                                    if(!vessicchio){///aggiungo il segmento
                                                        vettseg.push_back(new Segment);
                                                        Vertex* v1=new Vertex;
                                                        Vertex* v2=new Vertex;
                                                        *v1=vertice_trovato1;
                                                        *v2=vertice_da_controllare;
                                                        vettseg[indice]->Initialize(*v1, *v2);
                                                        vettseg[indice]->ComputeTangent();
                                                        face->AddSegment(*vettseg[indice]);
                                                        indice++;

                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                //ho calcolato i nuovi segmenti

                                ///alloco la memoria per il nuovo poliedro
                                convexPolyhedra.push_back(concavePolyhedron.Clone());
                                convexPolyhedra.push_back(concavePolyhedron.Clone());
                                //cout<<"alloco memoria"<<endl;

                                ///predispongo per accedere agli elementi del poliero e modificarli
                                list<IPolyhedron*>::iterator it = convexPolyhedra.end();
                                it--;
                                it--;
                                IPolyhedron& convexPolyhedron = **it;
                                list<IPolyhedron*>::iterator ita = it;
                                ita++;
                                IPolyhedron& convexPolyhedron2 = **ita;


                                ///vettore con le coordinate dei vertici
                                const vector<const Vertex*>& coordinate = concavePolyhedron.Vertices();

                                ///aggiungo i vertici
                                {
                                const Vector3d componenti = *face->GetPlaneNormal(); //copia dei coefficenti del piano per più agile utilizzo
                                for (unsigned int j=0;j<concavePolyhedron.NumberOfVertices();j++){
                                    Vector3d coordinate_vertice = *coordinate[j]; //copia delle coordinate dei vertici per più agile utilizzo

                                    ///controllo appartenenza vertice alla faccia
                                    if (componenti[0]*coordinate_vertice[0]+componenti[1]*coordinate_vertice[1]+componenti[2]*coordinate_vertice[2] > face->GetPlaneTranslation()- tolerance
                                        && componenti[0]*coordinate_vertice[0]+componenti[1]*coordinate_vertice[1]+componenti[2]*coordinate_vertice[2] < face->GetPlaneTranslation()+ tolerance){

                                        convexPolyhedron.AddVertex(concavePolyhedron.GetVertex(j));
                                        convexPolyhedron2.AddVertex(concavePolyhedron.GetVertex(j));
                                    }
                                    ///controllo posizione di un vertice non appartenente alla faccia rispetto alla faccia stessa
                                    else {
                                        if (componenti[0]*coordinate_vertice[0]+componenti[1]*coordinate_vertice[1]+componenti[2]*coordinate_vertice[2] > face->GetPlaneTranslation()){
                                            convexPolyhedron.AddVertex(concavePolyhedron.GetVertex(j));
                                        }
                                        else{
                                            convexPolyhedron2.AddVertex(concavePolyhedron.GetVertex(j));
                                        }
                                    }
                                }
                                }

                                ///aggiungo i segmenti
                                bool found1[face->NumberOfSegments()]={0};

                                for (unsigned int d=0;d<face->NumberOfSegments();d++){
                                    convexPolyhedron.AddSegment(face->GetSegment(d));
                                }
                                for(unsigned int n=0;n<concavePolyhedron.NumberOfSegments();n++){
                                    for (unsigned int m=0;m<convexPolyhedron.NumberOfVertices();m++){
                                        for (unsigned int h=0;h<convexPolyhedron.NumberOfVertices();h++){
                                            if (concavePolyhedron.GetSegment(n).Origin().IsEqual(convexPolyhedron.GetVertex(m))
                                                && concavePolyhedron.GetSegment(n).End().IsEqual(convexPolyhedron.GetVertex(h))){
                                                bool appartiene_a_face = 0;
                                                for (unsigned int d=0;d<face->NumberOfSegments();d++){
                                                    if ((concavePolyhedron.GetSegment(n).Origin().IsEqual(face->GetSegment(d).Origin())
                                                         && concavePolyhedron.GetSegment(n).End().IsEqual(face->GetSegment(d).End()))
                                                         || (concavePolyhedron.GetSegment(n).End().IsEqual(face->GetSegment(d).Origin())
                                                         && concavePolyhedron.GetSegment(n).Origin().IsEqual(face->GetSegment(d).End()))){
                                                        found1[d]=1;
                                                        appartiene_a_face=1;
                                                        ///ci interessa se il segmento non ha un corrispettivo nel poliedro, ovvero se giace su una
                                                        ///faccia che va tagliata lungo il segmento stesso
                                                    }
                                                }
                                                if(!appartiene_a_face){
                                                    convexPolyhedron.AddSegment(concavePolyhedron.GetSegment(n));
                                                }
                                            }
                                        }
                                    }
                                }

                                ///ripeto le stesse operazioni per l'altro poliedro ottenuto dal taglio
                                bool found2[face->NumberOfSegments()]={};

                                for (unsigned int d=0;d<face->NumberOfSegments();d++){
                                    convexPolyhedron2.AddSegment(face->GetSegment(d));
                                }
                                for(unsigned int n=0;n<concavePolyhedron.NumberOfSegments();n++){
                                    for (unsigned int m=0;m<convexPolyhedron2.NumberOfVertices();m++){
                                        for (unsigned int h=0;h<convexPolyhedron2.NumberOfVertices();h++){
                                            if (concavePolyhedron.GetSegment(n).Origin().IsEqual(convexPolyhedron2.GetVertex(m))
                                                && concavePolyhedron.GetSegment(n).End().IsEqual(convexPolyhedron2.GetVertex(h))){
                                                bool appartiene_a_face = 0;
                                                for (unsigned int d=0;d<face->NumberOfSegments();d++){
                                                    if ((concavePolyhedron.GetSegment(n).Origin().IsEqual(face->GetSegment(d).Origin())
                                                         && concavePolyhedron.GetSegment(n).End().IsEqual(face->GetSegment(d).End()))
                                                         || (concavePolyhedron.GetSegment(n).End().IsEqual(face->GetSegment(d).Origin())
                                                         && concavePolyhedron.GetSegment(n).Origin().IsEqual(face->GetSegment(d).End()))){
                                                        appartiene_a_face=1;
                                                        found2[d]=1;
                                                        ///ci interessa se il segmento non ha un corrispettivo nel poliedro, ovvero se giace su una
                                                        ///faccia che va tagliata lungo il segmento stesso
                                                    }
                                                }
                                                if(!appartiene_a_face){
                                                    convexPolyhedron2.AddSegment(concavePolyhedron.GetSegment(n));
                                                }
                                            }
                                        }
                                    }
                                }

                                ///aggiungo le facce

                                //POLIEDRO 1
                                unsigned int salto1[face->NumberOfSegments()]; //indica quali facce abbiamo già aggiunto come pezzo di faccia tagliata
                                for(unsigned int d=0;d<face->NumberOfSegments();d++){
                                    salto1[d]=concavePolyhedron.NumberOfFaces();
                                }
                                for(unsigned int d=0;d<face->NumberOfSegments();d++){
                                    if (!found1[d]){
                                        ///se found è true escludiamo a priori la possibilità che il segmento sia intersezione di due facce adiacenti
                                        ///per cui bastano due vertici a identificare univocamente la faccia su cui giace il segmento
                                        IPolygon* faccia_tagliata = new Polygon;
                                        for(unsigned int n=0;n<concavePolyhedron.NumberOfFaces();n++){
                                            for (unsigned int u=0;u<concavePolyhedron.GetFace(n).NumberOfVertices();u++){
                                                if (face->GetSegment(d).Origin()==concavePolyhedron.GetFace(n).GetVertex(u)){
                                                    for (unsigned int v=0;v<concavePolyhedron.GetFace(n).NumberOfVertices();v++){
                                                        if (face->GetSegment(d).End()==concavePolyhedron.GetFace(n).GetVertex(v)){
                                                            for (unsigned int ind=0;ind<concavePolyhedron.GetFace(n).NumberOfVertices();ind++){
                                                                for (unsigned int und=0;und<convexPolyhedron.NumberOfVertices();und++){
                                                                    if(concavePolyhedron.GetFace(n).GetVertex(ind)==convexPolyhedron.GetVertex(und)){
                                                                        faccia_tagliata->AddVertex(convexPolyhedron.GetVertex(und));
                                                                        //aggiungo un vertice
                                                                    }
                                                                }
                                                            }

                                                            faccia_tagliata->AddSegment(face->GetSegment(d)); //aggiungo segmento di intersezione tra faccia tagliata e faccia di taglio
                                                            for (unsigned int ind=0;ind<concavePolyhedron.GetFace(n).NumberOfSegments();ind++){
                                                                for (unsigned int und=0;und<convexPolyhedron.NumberOfSegments();und++){
                                                                    if (concavePolyhedron.GetFace(n).GetSegment(ind).Origin()==convexPolyhedron.GetSegment(und).Origin() && concavePolyhedron.GetFace(n).GetSegment(ind).End()==convexPolyhedron.GetSegment(und).End()){
                                                                        faccia_tagliata->AddSegment(convexPolyhedron.GetSegment(und));
                                                                    }
                                                                }
                                                            }
                                                        faccia_tagliata->ComputePlane();
                                                        faccia_tagliata->ComputeCentroid();
                                                        faccia_tagliata->ComputeRotatedVertices();

                                                        v=concavePolyhedron.GetFace(n).NumberOfVertices();
                                                        salto1[d]=n;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        //aggiungo la faccia tagliata al poliedro
                                        convexPolyhedron.AddFace(*faccia_tagliata);
                                    }
                                }
                                //aggiungo la faccia di taglio
                                convexPolyhedron.AddFace(*face);

                                for(unsigned int n=0;n<concavePolyhedron.NumberOfFaces();n++){
                                    bool salta=0;
                                    for(unsigned int d=0;d<face->NumberOfSegments() && salta==0;d++){
                                        if (n==salto1[d]){
                                            salta=1;
                                        }
                                    }
                                    ///cerco tre vertici del poliedro tagliato che appertengono a un'unica faccia del poliedro concavo
                                    ///e aggiunqo questa faccia al poliedro tagliato
                                    if (salta==0){
                                        for (unsigned int m=0;m<convexPolyhedron.NumberOfVertices();m++){
                                            for (unsigned int h=0;h<convexPolyhedron.NumberOfVertices();h++){
                                                for (unsigned int g=0;g<convexPolyhedron.NumberOfVertices();g++){
                                                    for (unsigned int u=0;u<concavePolyhedron.GetFace(n).NumberOfVertices()-2;u++){
                                                        if(concavePolyhedron.GetFace(n).GetVertex(u)==convexPolyhedron.GetVertex(m)
                                                            && concavePolyhedron.GetFace(n).GetVertex(u+1)==convexPolyhedron.GetVertex(h)
                                                            && concavePolyhedron.GetFace(n).GetVertex(u+2)==convexPolyhedron.GetVertex(g)){
                                                            if (&concavePolyhedron.GetFace(n)!=&convexPolyhedron.GetFace(convexPolyhedron.NumberOfFaces()-1)){
                                                                convexPolyhedron.AddFace(concavePolyhedron.GetFace(n));
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                ///Faccio le stesse operazioni che ho fatto per il primo poliedro anche per il secondo

                                ///Aggiungo le facce

                                //POLIEDRO 2
                                unsigned int salto2[face->NumberOfSegments()];
                                for(unsigned int d=0;d<face->NumberOfSegments();d++){
                                    salto2[d]=concavePolyhedron.NumberOfFaces();
                                }
                                for(unsigned int d=0;d<face->NumberOfSegments();d++){
                                    if (!found2[d]){
                                        ///se found è true escludiamo a priori la possibilità che il segmento sia intersezione di due facce adiacenti
                                        ///per cui bastano due vertici a identificare univocamente la faccia su cui giace il segmento
                                        IPolygon* faccia_tagliata = new Polygon;
                                        for(unsigned int n=0;n<concavePolyhedron.NumberOfFaces();n++){
                                            for (unsigned int u=0;u<concavePolyhedron.GetFace(n).NumberOfVertices();u++){
                                                if (face->GetSegment(d).Origin()==concavePolyhedron.GetFace(n).GetVertex(u)){
                                                    for (unsigned int v=0;v<concavePolyhedron.GetFace(n).NumberOfVertices();v++){
                                                        if (face->GetSegment(d).End()==concavePolyhedron.GetFace(n).GetVertex(v)){
                                                            for (unsigned int ind=0;ind<concavePolyhedron.GetFace(n).NumberOfVertices();ind++){
                                                                for (unsigned int und=0;und<convexPolyhedron2.NumberOfVertices();und++){
                                                                    if(concavePolyhedron.GetFace(n).GetVertex(ind)==convexPolyhedron2.GetVertex(und)){
                                                                        faccia_tagliata->AddVertex(convexPolyhedron2.GetVertex(und));
                                                                    }
                                                                }
                                                            }

                                                            faccia_tagliata->AddSegment(face->GetSegment(d)); //aggiungo segmento di intersezione tra faccia tagliata e faccia di taglio
                                                            for (unsigned int ind=0;ind<concavePolyhedron.GetFace(n).NumberOfSegments();ind++){
                                                                for (unsigned int und=0;und<convexPolyhedron2.NumberOfSegments();und++){
                                                                    if(concavePolyhedron.GetFace(n).GetSegment(ind).Origin()==convexPolyhedron2.GetSegment(und).Origin() && concavePolyhedron.GetFace(n).GetSegment(ind).End()==convexPolyhedron2.GetSegment(und).End()){
                                                                        faccia_tagliata->AddSegment(convexPolyhedron2.GetSegment(und));

                                                                    }
                                                                }
                                                            }
                                                        faccia_tagliata->ComputePlane();
                                                        faccia_tagliata->ComputeCentroid();
                                                        faccia_tagliata->ComputeRotatedVertices();

                                                        v=concavePolyhedron.GetFace(n).NumberOfVertices();
                                                        salto2[d]=n;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        convexPolyhedron2.AddFace(*faccia_tagliata);
                                    }
                                }

                                convexPolyhedron2.AddFace(*face);
                                for(unsigned int n=0;n<concavePolyhedron.NumberOfFaces();n++){
                                    bool salta=0;
                                    for(unsigned int d=0;d<face->NumberOfSegments() && salta==0;d++){
                                        if (n==salto2[d]){
                                            salta=1;
                                        }
                                    }

                                    ///cerco tre vertici del poliedro tagliato che appertengono a un'unica faccia del poliedro concavo
                                    ///e aggiunqo questa faccia al poliedro tagliato
                                    if (salta==0){
                                        for (unsigned int m=0;m<convexPolyhedron2.NumberOfVertices();m++){
                                            for (unsigned int h=0;h<convexPolyhedron2.NumberOfVertices();h++){
                                                for (unsigned int g=0;g<convexPolyhedron2.NumberOfVertices();g++){
                                                    for (unsigned int u=0;u<concavePolyhedron.GetFace(n).NumberOfVertices()-2;u++){
                                                        if(concavePolyhedron.GetFace(n).GetVertex(u)==convexPolyhedron2.GetVertex(m)
                                                            && concavePolyhedron.GetFace(n).GetVertex(u+1)==convexPolyhedron2.GetVertex(h)
                                                            && concavePolyhedron.GetFace(n).GetVertex(u+2)==convexPolyhedron2.GetVertex(g)){
                                                            if (&concavePolyhedron.GetFace(n)!=&convexPolyhedron2.GetFace(convexPolyhedron2.NumberOfFaces()-1)){
                                                                convexPolyhedron2.AddFace(concavePolyhedron.GetFace(n));
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                ///controllo se i poliedri ottenuti sono convessi: in tal caso l'i-esimo elemento di eseguisottrazione va a 1
                                ///se questo resta a 0 viene richiamata sul poliedro in questione la funzione per il taglio
                                bool eseguisottrazione[2]={0,0};
                                vector <int*> problemi1;
                                eseguisottrazione[0]=IsPolyhedronConvex(convexPolyhedron,tolerance,problemi1);
                                vector <int*> problemi2;
                                eseguisottrazione[1]=IsPolyhedronConvex(convexPolyhedron2,tolerance,problemi2);
                                if (!eseguisottrazione[0]){
                                    convexPolyhedra.erase(it); //elimino il poliedro dalla lista dei poliedri convessi
                                    ConcaveToConvexPolyhedron(convexPolyhedron,convexPolyhedra,tolerance,problemi1);
                                }
                                else{
                                    uscita=1;
                                }
                                if (!eseguisottrazione[1]){
                                    convexPolyhedra.erase(ita); //elimino il poliedro dalla lista dei poliedri convessi
                                    ConcaveToConvexPolyhedron(convexPolyhedron2,convexPolyhedra,tolerance,problemi2);
                                }
                                else{
                                    uscita=1;
                                }
                        }
                    }
                }
            }
        }
    }



    return Output::Success;
  }
  // ***************************************************************************


}
