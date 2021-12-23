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

#ifndef __PARALLELENVIRONMENT_H
#define __PARALLELENVIRONMENT_H

#include "MPI_Process.hpp"

namespace GeDiM
{
	class ParallelEnvironment;

	/// @brief UnitTest Base class
	class ParallelEnvironment
	{
		protected:
			static MPI_Process_Base process;

		public:
			static const MPI_Process_Base& Process() { return process; }

			/// Initialize the MPI Environment
			static Output::ExitCodes Initialize(int argc, char** argv);
			/// Finalize the MPI Environment
			static Output::ExitCodes Finalize();
	};
}

#endif // __PARALLELENVIRONMENT_H
