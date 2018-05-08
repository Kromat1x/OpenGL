Tema 1 EGC - Marius Bina 336CC

Astronaut - Astronautul este reprezentat de un triunghi echilateral care porneste din colt stanga jos al ferestrei. Acesta are varfurile colorate diferit, rosu reprezentand varful "navei".
			In momentul in care se primeste click stanga, astronautul se roteste cu varful spre punctul unde am dat click si pleaca in directia respectiva.

Asteroizi - Asteroizii sunt obtinuti prin alegerea unui numar de puncte de pe un cerc si unirea lor folosind GL_POLYGON ca mod de randare.

Coliziuni - Pentru coliziunea cu platformele se verifica daca cercul circumscris triunghiului care reprezinta astronautul se intersecteaza cu dreptunghiul reprezentat de platforma.
			Pentru coliziunea cu asteroizii ambele obiecte sunt reprezentate drept cercuri si coliziunea se face prin compararea sumei razelor cu distanta dintre centre.
			
Reflexie - Pentru reflexia de pe platforma se foloseste o oglindire a unui punct anterior peste dreapta perpendiculara pe platforma si apoi se apeleaza aceeasi functionalitate ca in cazul unui click,
			formula pentru oglindire este un particularizata pentru cazul in care platforma e orizontala.
			Pentru reflexia de pe asteroid se foloseste o metoda asemanatoare, dar generalizata pentru orice directie a dreptei normale.