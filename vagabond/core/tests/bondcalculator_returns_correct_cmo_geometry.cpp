#include "../Cif2Geometry.h"
#include "../AtomGroup.h"
#include "../BondAngle.h"
#include "../BondLength.h"
#include "../BondCalculator.h"
#include "bondcalculator_checks_geometry_for_ligand.h"

int main()
{
	std::string path = "/assets/geometry/CMO.cif";

	return checkGeometry(path);
}

