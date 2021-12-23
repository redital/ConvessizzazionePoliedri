#ifndef __MPI_PROCESS_H
#define __MPI_PROCESS_H

#include <vector>
#include <string>

#include "Output.hpp"
#include "Eigen"
using namespace Eigen;

#include <algorithm>

#if USE_MPI == 1
#include <mpi.h>
using	namespace MPI;
#endif


#if USE_PETSC == 1
#include "petscvec.h"
#endif

using namespace std;
using namespace MainApplication;

namespace GeDiM
{
	class MPI_Process_Base;
	class MPIExtensions;


	class MPI_Process_Base
	{
		protected:
			unsigned int rank; ///< Rank of the process
			unsigned int numberProcesses; ///< Number of all the processes of the MPI simulation
			bool isActive; ///< Tells if the process is active


		public:
			MPI_Process_Base();
			virtual ~MPI_Process_Base();



			const unsigned int& Rank() const { return rank; }
			const unsigned int& NumberProcesses() const { return numberProcesses; }
			const bool& IsActive() const { return isActive; }

			virtual Output::ExitCodes Initialize(const unsigned int& _rank, const unsigned int& _numberProcesses, const bool& _isActive = true);
			virtual Output::ExitCodes Initialize(const void* mpiCommunicatorPointer = NULL);

			virtual void Summary();

	};

	class MPIExtensions
	{
		private:
			static int mpiSendTag; ///< Tag used for MPI send communications
			static int mpiRecvTag; ///< Tag used for MPI receive communications
		public:
			static int MpiSendTag(const int& numSends = 1) { int tag = mpiSendTag; mpiSendTag += numSends; return tag; }
			static int MpiRecvTag(const int& numRecvs = 1) { int tag = mpiRecvTag; mpiRecvTag += numRecvs; return tag; }
	};


}


#endif // __MPI_PROCESS_H

