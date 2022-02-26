set(VAGABOND_SRC
	 ${PROJECT_SOURCE_DIR}/core/src/AlignmentTool.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/Atom.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/AtomGroup.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/BondAngle.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/BondCalculator.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/BondLength.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/BondSequence.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/BondSequenceHandler.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/BondTorsion.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/Chirality.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/Cif2Geometry.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/ConcertedBasis.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/GeometryTable.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/HasBondstraints.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/Knotter.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/matrix_functions.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/PositionRefinery.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/SimpleBasis.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/SimplexEngine.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/Superpose.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/ThreadCalculatesBondSequence.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/ThreadExtractsBondPositions.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/ThreadMiniJobForSequence.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/ThreadSubmitsJobs.cpp
	 ${PROJECT_SOURCE_DIR}/core/src/TorsionBasis.cpp
)

add_library(libbond STATIC ${VAGABOND_SRC})
set_target_properties(libbond PROPERTIES OUTPUT_NAME bond)
#include the GLM directory - i have built it from source and install
#directory has a CMakeConfig file which can also be used - try later
target_include_directories(libbond PUBLIC ${glm_path}/install/include/glm)
target_include_directories(libbond PUBLIC ${PROJECT_SOURCE_DIR}/utils)
target_include_directories(libbond PUBLIC ${PROJECT_SOURCE_DIR}/utils/svd/include)
target_include_directories(libbond PUBLIC ${PROJECT_SOURCE_DIR}/utils/)
target_include_directories(libbond PUBLIC ${PROJECT_SOURCE_DIR}/core/include)
target_include_directories(libbond PUBLIC ${PROJECT_SOURCE_DIR}/utils/reader/include)
target_include_directories(libbond PUBLIC ${gemmi_path}/install/include)

add_executable(simple_basis_torsion 
	${PROJECT_SOURCE_DIR}/core/tests/simplebasis_returns_angle_for_requested_torsion.cpp)
target_include_directories(simple_basis_torsion PUBLIC 
	${PROJECT_SOURCE_DIR}/core/include
        ${PROJECT_SOURCE_DIR}/utils
        ${glm_path}/install/include/glm)
target_link_libraries(simple_basis_torsion PUBLIC libbond pthread)

if (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    target_compile_options(libbond PUBLIC -Wall -Wextra -pedantic)
    target_compile_options(libbond PUBLIC -xHost)
    target_compile_definitions(libbond PRIVATE -DAVX2 -DSSE2)
endif (CMAKE_CXX_COMPILER_ID MATCHES "Intel")

