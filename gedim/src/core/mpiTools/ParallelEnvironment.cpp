// Copyright (C) 2020 Vicini Fabio
//
// This file is part of the dissertation of the author.
//
// This is a free program: you can redistribute it and/or modify
// it under the terms of the author.
//
// This program is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.
//
// Modified by Vicini Fabio 2020
//
// First added:  2020-01-17

#if USE_PETSC
#include "petsc.h"
#endif
#if USE_MPI == 1
#include "MPI_Process.hpp"
#endif

#include "ParallelEnvironment.hpp"

namespace GeDiM
{
	// ***************************************************************************
	MPI_Process_Base ParallelEnvironment::process = MPI_Process_Base();
	// ***************************************************************************
	Output::ExitCodes ParallelEnvironment::Initialize(int argc, char** argv)
	{
#if USE_PETSC == 1
		PetscInitialize(&argc, &argv, NULL, NULL);
#elif USE_MPI == 1
		MPI::Init(argc, argv);
#endif

		unsigned int rank = 0;
		unsigned int numberProcesses = 1;

#if USE_MPI == 1
		MPI_Comm_rank(MPI_COMM_WORLD, (int*)&rank);
		MPI_Comm_size(MPI_COMM_WORLD, (int*)&numberProcesses);
#endif // USE_MPI

		process.Initialize(rank, numberProcesses, true);

		return Output::Success;
	}
	// ***************************************************************************
	Output::ExitCodes ParallelEnvironment::Finalize()
	{
#if USE_PETSC == 1
		PetscFinalize();
#elif USE_MPI == 1
		MPI::Finalize();
#endif
	}
	// ***************************************************************************
}
