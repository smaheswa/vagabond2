#include "../Cif2Geometry.h"
#include "../AtomGroup.h"
#include "../Chirality.h"

int main()
{
	std::string path = "/assets/geometry/ASP.cif";

	Cif2Geometry geom = Cif2Geometry(path);
	geom.parse();
	
	AtomGroup *atoms = geom.atoms();
	
	Atom *ca = atoms->firstAtomWithName("CA");
	Atom *cb = atoms->firstAtomWithName("CB");
	Atom *n = atoms->firstAtomWithName("N");
	Atom *c = atoms->firstAtomWithName("C");
	Atom *h = atoms->firstAtomWithName("HA");

	Chirality *ch = ca->chirality(0);
	int sign = ch->get_sign(&h, &n, &c, &cb);
	
	return !(sign == 1);
}
