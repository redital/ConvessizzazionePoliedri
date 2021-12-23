#include "MPI_Process.hpp"
#if USE_MPI == 1
#include "mpi.h"
#endif
#if USE_PETSC == 1
#include "petscvec.h"
#endif
#if ENABLE_METIS
#include "metis.h"
#endif

namespace GeDiM
{
	// ***************************************************************************
	// MPIProcess_Base Implementation
	// ***************************************************************************
	MPI_Process_Base::MPI_Process_Base()
	{
		rank = 0;
		numberProcesses = 1;
		isActive = true;
	}
	MPI_Process_Base::~MPI_Process_Base()
	{

	}
	// ***************************************************************************
	Output::ExitCodes MPI_Process_Base::Initialize(const unsigned int& _rank, const unsigned int& _numberProcesses, const bool& _isActive)
	{
		rank = _rank;
		numberProcesses = _numberProcesses;
		isActive = _isActive;
	}
	// ***************************************************************************
	Output::ExitCodes MPI_Process_Base::Initialize(const void* mpiCommunicatorPointer)
	{
#if USE_MPI == 1
		const MPI_Comm& communicator = (mpiCommunicatorPointer == NULL) ? MPI_COMM_WORLD : *(MPI_Comm*)mpiCommunicatorPointer;
		MPI_Comm_rank(communicator, (int*)&rank);
		MPI_Comm_size(communicator, (int*)&numberProcesses);
		isActive = true;
#else
		rank = 0;
		numberProcesses = 1;
		isActive = true;
#endif // USE_MPI

		return Output::Success;
	}
	// ***************************************************************************
	void MPI_Process_Base::Summary()
	{
		string activeLabel = (isActive ? "Active" : "Not Active");

		Output::PrintLine('-', true);
		Output::PrintGenericMessage("Process %d / %d - %s", false, rank, numberProcesses, activeLabel.c_str());
		Output::PrintLine('-', true);
	}
	//****************************************************************************
	//  ***************************************************************************
	int MPIExtensions::mpiSendTag = 1;
	int MPIExtensions::mpiRecvTag = 1;
	// ***************************************************************************

}
