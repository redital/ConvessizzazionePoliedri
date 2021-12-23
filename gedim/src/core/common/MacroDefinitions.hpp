#ifndef __MACROPARAMETERS_H
#define __MACROPARAMETERS_H

/// Use MPI
/// - 0 false
/// - 1 true
#define USE_MPI 0

/// Use PETSC
/// - 0 false
/// - 1 true
#define PETSC 0

/// Use VTK library
/// - 0 VTK not enabled
/// - 1 VTK enabled
#define ENABLE_VTK 0

/// Use METIS library
/// - 0 METIS not enabled
/// - 1 METIS enabled
#define ENABLE_METIS 0

/// Verbose Levels
/// - 0 None
/// - 1 Error
/// - 2 Warning
/// - 3 Info
/// - 4 Debug
#define VERBOSE 3

/// Logging Levels
/// - 0 None
/// - 1 Only Console
/// - 2 Only Files
/// - 3 Console and Files
#define LOGGING 3

/// @name Code Simplifications
///@{
#ifndef MIN
#define MIN(a,b) (a < b) ? a : b
#endif

#ifndef MAX
#define MAX(a,b) (a > b) ? a : b
#endif
///@}

#endif
