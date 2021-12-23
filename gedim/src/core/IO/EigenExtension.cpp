#include "EigenExtension.hpp"
#include <iostream>

#include "ConfigFile.hpp"

using namespace std;
using namespace Configuration;

namespace MainApplication
{
	// ***************************************************************************
	ostream& EigenExtension::PrintVector(ostream& out, const VectorXd& vec)
	{
		const int& maxElementToPrint = ConfigFile::DebugParam().MaxNumElementToPrint();
		const int& startingIndex = ConfigFile::DebugParam().StartingIndexToPrint();

		unsigned int sizeVector = (maxElementToPrint == 0 || maxElementToPrint > (int)vec.size()) ? vec.size() : maxElementToPrint;
		unsigned int startIndexVector = (startingIndex >= (int)vec.size()) ? 0 : startingIndex;

		out<< "[";
		for (unsigned int i = startIndexVector; i < startIndexVector + sizeVector && i < vec.size(); i++)
			out<< (i != startIndexVector ? "," : "")<< vec(i);
		out<< "]";

		return out;
	}
	// ***************************************************************************
	ostream& EigenExtension::PrintVector(ostream& out, const Map<const VectorXd>& vec)
	{
		const int& maxElementToPrint = ConfigFile::DebugParam().MaxNumElementToPrint();
		const int& startingIndex = ConfigFile::DebugParam().StartingIndexToPrint();

		unsigned int sizeVector = (maxElementToPrint == 0 || maxElementToPrint > (int)vec.size()) ? vec.size() : maxElementToPrint;
		unsigned int startIndexVector = (startingIndex >= (int)vec.size()) ? 0 : startingIndex;

		out<< "[";
		for (unsigned int i = startIndexVector; i < startIndexVector + sizeVector && i < vec.size(); i++)
			out<< (i != startIndexVector ? "," : "")<< vec(i);
		out<< "]";

		return out;
	}
	// ***************************************************************************
	const Output::ExitCodes EigenExtension::ReadFromBinaryFile(const string& nameFile, VectorXd& dataToRead, const unsigned int& dataSizeToRead, const unsigned int& startingPosition)
	{
		/// <ul>

		/// <li> Get file dimension
		unsigned int fileSize = 0;

		if (dataSizeToRead == 0)
		{
			Output::ExitCodes result = Output::GetBinaryFileSize(nameFile, fileSize, sizeof(double), startingPosition);
			if (result != Output::Success)
				return result;

			if (fileSize == 0)
				return Output::Success;
		}

		int fileContentSize = dataSizeToRead == 0 ? fileSize / sizeof(double) : dataSizeToRead;

		if (fileContentSize == 0)
		{
			Output::PrintErrorMessage("Error in file '%s': uncorrect content size. Obtained %d", false, nameFile.c_str(), fileContentSize);
			return Output::GenericError;
		}

		dataToRead.resize(fileContentSize);
		Output::ExitCodes result = Output::ReadBinaryFile(nameFile, dataToRead.data(), sizeof(double), fileContentSize, startingPosition);

		return result;

		/// </ul>
	}
	// ***************************************************************************
	const Output::ExitCodes EigenExtension::WriteToBinaryFile(const string& nameFile, const VectorXd& vec, const unsigned int& dataSizeToWrite, const unsigned int& dataStartingPositionToWrite, const bool& append)
	{
		/// <ul>

		if (dataSizeToWrite > vec.size())
		{
			Output::PrintErrorMessage("Error in write file '%s': uncorrect size. Required %d, given %d", false, nameFile.c_str(), dataSizeToWrite, vec.size());
			return Output::GenericError;
		}

		if (dataStartingPositionToWrite > vec.size())
		{
			Output::PrintErrorMessage("Error in write file '%s': uncorrect starting position. Required %d, given %d", false, nameFile.c_str(), dataStartingPositionToWrite, vec.size());
			return Output::GenericError;
		}

		unsigned int fileDataSize = (dataSizeToWrite == 0) ? vec.size() : dataSizeToWrite;

		if (fileDataSize == 0)
			return Output::Success;

		/// <li> Exporting file
		Output::ExitCodes result = Output::WriteBinaryFile(nameFile, vec.data() + dataStartingPositionToWrite, sizeof(double), fileDataSize, append);

		return result;

		/// </ul>
	}
	// ***************************************************************************
	const Output::ExitCodes EigenExtension::ReadFromBinaryFile(const string& nameFile, Map<VectorXd>& dataToRead, const unsigned int& dataSizeToRead, const unsigned int& startingPosition)
	{
		/// <ul>

		/// <li> Get file dimension
		unsigned int fileSize = 0;

		if (dataSizeToRead == 0)
		{
			Output::ExitCodes result = Output::GetBinaryFileSize(nameFile, fileSize, sizeof(double), startingPosition);
			if (result != Output::Success)
				return result;

			if (fileSize == 0)
				return Output::Success;
		}

		int fileContentSize = dataSizeToRead == 0 ? fileSize / sizeof(double) : dataSizeToRead;

		if (fileContentSize == 0)
		{
			Output::PrintErrorMessage("Error in file '%s': uncorrect content size. Obtained %d", false, nameFile.c_str(), fileContentSize);
			return Output::GenericError;
		}

		dataToRead.resize(fileContentSize);
		Output::ExitCodes result = Output::ReadBinaryFile(nameFile, dataToRead.data(), sizeof(double), fileContentSize, startingPosition);

		return result;

		/// </ul>
	}
	// ***************************************************************************
	const Output::ExitCodes EigenExtension::WriteToBinaryFile(const string& nameFile, const Map<const VectorXd>& vec, const unsigned int& dataSizeToWrite, const unsigned int& dataStartingPositionToWrite, const bool& append)
	{
		/// <ul>

		if (dataSizeToWrite > vec.size())
		{
			Output::PrintErrorMessage("Error in write file '%s': uncorrect size. Required %d, given %d", false, nameFile.c_str(), dataSizeToWrite, vec.size());
			return Output::GenericError;
		}

		if (dataStartingPositionToWrite > vec.size())
		{
			Output::PrintErrorMessage("Error in write file '%s': uncorrect starting position. Required %d, given %d", false, nameFile.c_str(), dataStartingPositionToWrite, vec.size());
			return Output::GenericError;
		}

		unsigned int fileDataSize = (dataSizeToWrite == 0) ? vec.size() : dataSizeToWrite;

		if (fileDataSize == 0)
			return Output::Success;

		/// <li> Exporting file
		Output::ExitCodes result = Output::WriteBinaryFile(nameFile, vec.data() + dataStartingPositionToWrite, sizeof(double), fileDataSize, append);

		return result;

		/// </ul>
	}
	// ***************************************************************************
	const Output::ExitCodes EigenExtension::ReadFromBinaryFile(const string& nameFile, unsigned int& rows, unsigned int& cols, vector< Triplet<double> >& triplets, const unsigned int& startingPosition)
	{
		vector<double> vectorToImport;

		if (!Output::ReadBinaryFile(nameFile, vectorToImport, 0, startingPosition))
		{
			Output::PrintErrorMessage("Error in read matrix from file '%s'", false, nameFile.c_str());
			return Output::GenericError;
		}

		if (vectorToImport.size() < 3)
		{
			Output::PrintErrorMessage("Error in read matrix from file '%s': no enough information get from file", false, nameFile.c_str());
			return Output::GenericError;
		}

		rows = vectorToImport[0];
		cols = vectorToImport[1];
		unsigned int nonZeros = vectorToImport[2];

		if (rows == 0)
		{
			Output::PrintErrorMessage("Error in read matrix from file '%s': no rows value", false, nameFile.c_str());
			return Output::GenericError;
		}

		if (cols == 0)
		{
			Output::PrintErrorMessage("Error in read matrix from file '%s': no cols value", false, nameFile.c_str());
			return Output::GenericError;
		}

		if (nonZeros == 0)
		{
			Output::PrintErrorMessage("Error in read matrix from file '%s': no nonZeros value", false, nameFile.c_str());
			return Output::GenericError;
		}

		if (vectorToImport.size() - 3 < 3 * nonZeros)
		{
			Output::PrintErrorMessage("Error in read matrix from file '%s': no enough non zeros values", false, nameFile.c_str());
			return Output::GenericError;
		}

		triplets.clear();
		triplets.reserve(nonZeros);

		for (unsigned int counter = 0; counter < 3 * nonZeros; counter += 3)
			triplets.push_back(Triplet<double>(vectorToImport[3 + counter], vectorToImport[3 + counter + 1], vectorToImport[3 + counter + 2]));

		return Output::Success;
	}
	// ***************************************************************************
	const Output::ExitCodes EigenExtension::ReadFromBinaryFile(const string& nameFile, SparseMatrix<double, RowMajor>& matrix, const unsigned int& startingPosition)
	{
		unsigned int rows, cols;
		vector< Triplet<double> > triplets;

		Output::ExitCodes result = ReadFromBinaryFile(nameFile, rows, cols, triplets, startingPosition);
		if (result != Output::Success)
		{
			Output::PrintErrorMessage("Error in read matrix from file '%s'", false, nameFile.c_str());
			return Output::GenericError;
		}

		matrix.resize(rows, cols);

		matrix.setFromTriplets(triplets.begin(), triplets.end());
		matrix.makeCompressed();

		return Output::Success;
	}
	// ***************************************************************************
	const Output::ExitCodes EigenExtension::ReadFromBinaryFile(const string& nameFile, SparseMatrix<double, ColMajor>& matrix, const unsigned int& startingPosition)
	{
		unsigned int rows, cols;
		vector< Triplet<double> > triplets;

		Output::ExitCodes result = ReadFromBinaryFile(nameFile, rows, cols, triplets, startingPosition);
		if (result != Output::Success)
		{
			Output::PrintErrorMessage("Error in read matrix from file '%s'", false, nameFile.c_str());
			return Output::GenericError;
		}

		matrix.resize(rows, cols);

		matrix.setFromTriplets(triplets.begin(), triplets.end());
		matrix.makeCompressed();

		return Output::Success;
	}
	// ***************************************************************************
	const Output::ExitCodes EigenExtension::WriteToBinaryFile(const string& nameFile, const SparseMatrix<double, RowMajor>& matrix, const UpLoType& matrixType, const bool& append)
	{
		unsigned int nonZeros = matrix.nonZeros();

		if (nonZeros == 0)
		{
			Output::PrintErrorMessage("Error in write matrix to file '%s': empty matrix", false, nameFile.c_str());
			return Output::GenericError;
		}

		vector<double> vectorToExport;
		unsigned int dimension = 3 + nonZeros * 3;
		vectorToExport.reserve(dimension);

		vectorToExport.push_back(matrix.rows());
		vectorToExport.push_back(matrix.cols());
		vectorToExport.push_back(0);

		for (int k = 0; k < matrix.outerSize(); ++k)
		{
			for (SparseMatrix<double, RowMajor>::InnerIterator it(matrix, k); it; ++it)
			{
				switch (matrixType) {
					case Lower:
						if (it.row() < it.col())
							continue;
						break;
					case Upper:
						if (it.row() > it.col())
							continue;
						break;
					default:
						break;
				}

				vectorToExport.push_back(it.row());
				vectorToExport.push_back(it.col());
				vectorToExport.push_back(it.value());
			}
		}
		vectorToExport.shrink_to_fit();
		dimension = vectorToExport.size();
		vectorToExport[2] = (dimension - 3) / 3;

		if (!Output::WriteBinaryFile(nameFile, vectorToExport, dimension, 0, append))
			return Output::GenericError;

		return Output::Success;
	}
	// ***************************************************************************
	const Output::ExitCodes EigenExtension::WriteToBinaryFile(const string& nameFile, const SparseMatrix<double, ColMajor>& matrix, const UpLoType& matrixType, const bool& append)
	{
		unsigned int nonZeros = matrix.nonZeros();

		if (nonZeros == 0)
		{
			Output::PrintErrorMessage("Error in write matrix to file '%s': empty matrix", false, nameFile.c_str());
			return Output::GenericError;
		}

		vector<double> vectorToExport;
		unsigned int dimension = 3 + nonZeros * 3;
		vectorToExport.reserve(dimension);

		vectorToExport.push_back(matrix.rows());
		vectorToExport.push_back(matrix.cols());
		vectorToExport.push_back(0);

		for (int k = 0; k < matrix.outerSize(); ++k)
		{
			for (SparseMatrix<double, ColMajor>::InnerIterator it(matrix, k); it; ++it)
			{
				switch (matrixType) {
					case Lower:
						if (it.row() < it.col())
							continue;
						break;
					case Upper:
						if (it.row() > it.col())
							continue;
						break;
					default:
						break;
				}

				vectorToExport.push_back(it.row());
				vectorToExport.push_back(it.col());
				vectorToExport.push_back(it.value());
			}
		}
		vectorToExport.shrink_to_fit();
		dimension = vectorToExport.size();
		vectorToExport[2] = (dimension - 3) / 3;

		if (!Output::WriteBinaryFile(nameFile, vectorToExport, dimension, 0, append))
			return Output::GenericError;

		return Output::Success;
	}
	// ***************************************************************************
}
