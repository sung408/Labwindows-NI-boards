#ifndef SQL_INCLUDE
#define SQL_INCLUDE 1

#if defined(INCLUDE_AFTER_WINDOWS_H) && !defined(_INC_WINDOWS)
#error  This header must be included before utility.h and formatio.h
#error  because this header includes Windows SDK headers.
#endif /* INCLUDE_AFTER_WINDOWS_H */

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef SQLFUNC
	#ifdef _NI_mswin16_
		#define SQLFUNC
	#else
		#define SQLFUNC __stdcall
	#endif
#endif


#ifndef SQLCDECL
	#ifdef _NI_mswin16_
		#define SQLCDECL
	#else
	#if defined(__WATCOMC__) || defined(_NI_WC_)
		#define SQLCDECL
	    #else
	    #define SQLCDECL __cdecl
	#endif
	#endif
#endif

#ifndef SQLSTDCALL
	#ifdef _NI_mswin16_
		#define SQLSTDCALL
	#else
		#define SQLSTDCALL __stdcall
	#endif
#endif

#if defined(_CVI_) && _CVI_ < 500
	#ifndef ENABLE_VARIANTS
		#define ENABLE_VARIANTS 0
	#endif
#else
	#define ENABLE_VARIANTS 1
#endif

#if ENABLE_VARIANTS		
#include <ole2.h>
#else
#include <stdarg.h>
#endif


/* connection, command or recordset open/closed state */
typedef enum {
	DB_OBJECT_STATE_CLOSED = 0,
	DB_OBJECT_STATE_OPEN = 1,
	DB_OBJECT_STATE_FORCE_TO_FOUR_BYTES = -1
} tDBObjectState;

/* database cursor type */
typedef enum {
	DB_CURSOR_TYPE_UNSPECIFIED = -1,
	DB_CURSOR_TYPE_FORWARD_ONLY = 0,
	DB_CURSOR_TYPE_KEYSET = 1,
	DB_CURSOR_TYPE_DYNAMIC = 2,
	DB_CURSOR_TYPE_STATIC = 3,
	DB_CURSOR_TYPE_FORCE_TO_FOUR_BYTES = -1
} tDBCursorType;

/* record set lock type */
typedef enum {
	DB_LOCK_UNSPECIFIED = -1,
	DB_LOCK_READ_ONLY = 1,
	DB_LOCK_PESSIMISTIC = 2,
	DB_LOCK_OPTIMISTIC = 3,
	DB_LOCK_BATCH_OPTIMISTIC = 4,
	DB_LOCK_TYPE_FORCE_TO_FOUR_BYTES = -1
}tDBLockType;

/* command type */
typedef enum {
	DB_COMMAND_UNSPECIFIED = -1,
	DB_COMMAND_UNKNOWN = 8,
	DB_COMMAND_TEXT = 1,
	DB_COMMAND_TABLE = 2,
	DB_COMMAND_STORED_PROC = 4,
	DB_COMMAND_FORCE_TO_FOUR_BYTES = -1
} tDBCommandType;

/* edit mode of current record */
typedef enum {
	DB_EDIT_MODE_NONE = 0,
	DB_EDIT_MODE_IN_PROGRESS = 1,
	DB_EDIT_MODE_ADD = 2,
	DB_EDIT_MODE_DELETE = 4,
	DB_EDIT_MODE_FORCE_TO_FOUR_BYTES = -1
} tDBEditMode;

/* connection mode */
typedef enum {
	DB_CONN_MODE_UNKNOWN = 0,
	DB_CONN_MODE_READ = 1,
	DB_CONN_MODE_WRITE = 2,
	DB_CONN_MODE_READ_WRITE = 3,
	DB_CONN_MODE_SHARE_DENY_READ = 4,
	DB_CONN_MODE_SHARE_DENY_WRITE = 8,
	DB_CONN_MODE_SHARE_EXCLUSIVE = 12,
	DB_CONN_MODE_SHARE_DENY_NONE = 16,
	DB_CONN_MODE_FORCE_TO_FOUR_BYTES = -1
} tDBConnectionMode;

/* filter type for statements */
typedef enum {
	DB_FILTER_NONE = 0,
	DB_FILTER_PENDING = 1,
	DB_FILTER_AFFECTED = 2,
	DB_FILTER_FETCHED = 3,
	DB_FILTER_FORCE_TO_FOUR_BYTES = -1
} tDBFilter;

/* marshal option */
typedef enum {
	DB_MARSHAL_OPT_ALL = 0,
	DB_MARSHAL_OPT_MODIF_ONLY = 1,
	DB_MARSHAL_OPT_FORCE_TO_FOUR_BYTES = -1
}tDBMarshalOpt;

/* which records are affected by batch update */
typedef enum {
	DB_AFFECT_CURRENT = 1,
	DB_AFFECT_GROUP = 2,
	DB_AFFECT_ALL = 3,
	DB_AFFECT_FORCE_TO_FOUR_BYTES = -1
}tDBAffect;

/* current record status */
typedef enum {
	DB_REC_STATUS_OK = 0,
	DB_REC_STATUS_NEW = 1,
	DB_REC_STATUS_MODIFIED = 2,
	DB_REC_STATUS_DELETED = 4,
	DB_REC_STATUS_UNMODIFIED = 8,
	DB_REC_STATUS_INVALID = 16,
	DB_REC_STATUS_MULTIPLE_CHANGES = 64,
	DB_REC_STATUS_PENDING_CHANGES = 128,
	DB_REC_STATUS_CANCELED = 256,
	DB_REC_STATUS_CANT_RELEASE = 1024,
	DB_REC_STATUS_CONCURRENCY_VIOLATION = 2048,
	DB_REC_STATUS_INTEGRITY_VILOATION = 4096,
	DB_REC_STATUS_MAX_CHANGES_EXCEEDED = 8192,
	DB_REC_STATUS_OBJECT_OPEN = 16384,
	DB_REC_STATUS_OUT_OF_MEMORY = 32768,
	DB_REC_STATUS_PERMISSION_DENIED = 65536,
	DB_REC_STATUS_SCHEMA_VIOLATION = 131072,
	DB_REC_STATUS_DBDELETED = 262144,
	DB_REC_STATUS_FORCE_TO_FOUR_BYTES = -1
}tDBRecStatus;

/* schema types for DBOpenSchema */
typedef enum {
	DB_SCHEMA_PROVIDER_SPECIFIC = -1,
	DB_SCHEMA_ASSERTS = 0,
	DB_SCHEMA_CATALOGS = 1,
	DB_SCHEMA_CHARACTER_SETS = 2,
	DB_SCHEMA_COLLATIONS = 3,
	DB_SCHEMA_COLUMNS = 4,
	DB_SCHEMA_CHECK_CONSTRAINTS = 5,
	DB_SCHEMA_CONSTRAINT_COLUMN_USAGE = 6,
	DB_SCHEMA_CONSTRAINT_TABLE_USAGE = 7,
	DB_SCHEMA_KEY_COLUMN_USAGE = 8,
	DB_SCHEMA_REFERENTIAL_CONSTRAINTS = 9,
	DB_SCHEMA_TABLE_CONSTRAINSTS = 10,
	DB_SCHEMA_COLUMN_DOMAIN_USAGE = 11,
	DB_SCHEMA_INDEXES = 12,
	DB_SCHEMA_COLUMN_PRIVILEGES = 13,
	DB_SCHEMA_TABLE_PRIVILEGES = 14,
	DB_SCHEMA_USAGE_PRIVILEGES = 15,
	DB_SCHEMA_PROCEDURE = 16,
	DB_SCHEMA_SCHEMATA = 17,
	DB_SCHEMA_SQL_LANGUAGES = 18,
	DB_SCHEMA_STATISTICS = 19,
	DB_SCHEMA_TABLES = 20,
	DB_SCHEMA_TRANSLATIONS = 21,
	DB_SCHEMA_PROVIDER_TYPES = 22,
	DB_SCHEMA_VIEWS = 23,
	DB_SCHEMA_VIEW_COLUMN_USAGE = 24,
	DB_SCHEMA_VIEW_TABLE_USAGE = 25,
	DB_SCHEMA_PROCEDURE_PARAMETERS = 26,
	DB_SCHEMA_FOREIGN_KEYS = 27,
	DB_SCHEMA_PRIMARY_KEYS = 28,
	DB_SCHEMA_PROCEDURE_COLUMNS = 29,
	DB_SCHEMA_FORCE_TO_FOUR_BYTES = -1
} tDBSchemaType;

/* whether to use a record set only or a record set and a command */
typedef enum {
	DB_USE_RECORDSET_ONLY = 2,
	DB_USE_COMMAND = 1,
	DB_USE_COMMAND_FORCE_TO_FOUR_BYTES = -1
} tDBUseCommandValues;

/* SQL parameter direction */
typedef enum  {
	DB_PARAM_UNKNOWN = 0,
	DB_PARAM_INPUT = 1,
	DB_PARAM_OUTPUT = 2,
	DB_PARAM_INPUT_OUTPUT = 3,
	DB_PARAM_RETURN_VALUE = 4,
	DB_PARAM_DIR_FORCE_TO_FOUR_BYTES = -1
}tDBParameterDirection;

/* field/column data types */
typedef enum {
	DB_EMPTY = 0,
	DB_TINYINT = 16,
	DB_SMALLINT = 2,
	DB_INTEGER = 3,
	DB_BIGINT = 20,
	DB_UNSIGNEDTINYINT = 17,
	DB_UNSIGNEDSMALLINT = 18,
	DB_UNSIGNEDINT = 19,
	DB_UNSIGNEDBIGINT = 21,
	DB_FLOAT = 4,
	DB_DOUBLEPRECISION = 5,
	DB_CURRENCY = 6,
	DB_DECIMAL = 14,
	DB_NUMERIC = 131,
	DB_BOOLEAN = 11,
	DB_ERROR = 10,
	DB_USERDEFINED = 132,
	DB_VARIANT = 12,
	DB_IDDISPATCH = 9,
	DB_IUNKNOWN = 13,
	DB_GUID = 72,
	DB_DATE = 7,                            /* double, days_since_1899_12_30.fraction_of_day */
	DB_DBDATE = 133,                        /* yyyymmdd */
	DB_TIME = 134,                      /* hhmmss */
	DB_DATETIME = 135,                      /* yyyymmddhhmmss plus a fraction in billionths */
	DB_BSTR = 8,
	DB_CHAR = 129,
	DB_VARCHAR = 200,
	DB_LONGVARCHAR = 201,
	DB_WCHAR = 130,
	DB_VARWCHAR = 202,
	DB_LONGVARWCHAR = 203,
	DB_BINARY = 128,
	DB_VARBINARY = 204,
	DB_LONGVARBINARY = 205,
	DB_DATA_TYPE_FORCE_TO_FOUR_BYTES = -1
}tDBDataType;


/* connection attributes */
typedef enum {
	ATTR_DB_CONN_CONNECTION_STRING =        0x00000000,
	ATTR_DB_CONN_COMMAND_TIMEOUT =          0x00000002,
	ATTR_DB_CONN_CONNECTION_TIMEOUT =   0x00000003,
	ATTR_DB_CONN_VERSION =                  0x00000004,
	ATTR_DB_CONN_DEFAULT_DATABASE =         0x0000000C,
	ATTR_DB_CONN_ISOLATION_LEVEL =          0x0000000D,
	ATTR_DB_CONN_ATTRIBUTES =               0x0000000E,
	ATTR_DB_CONN_CURSOR_LOCATION =          0x0000000F,
	ATTR_DB_CONN_MODE =                     0x00000010,
	ATTR_DB_CONN_PROVIDER =                 0x00000011,
	ATTR_DB_CONN_STATE =                    0x00000012,
	ATTR_DB_CONN_CONNECTION_OBJECT =        0x00000099,
	ATTR_DB_CONN_FORCE_TO_FOUR_BYTES = -1
} tDBConnectionAttr;

/* statement attributes */
typedef enum {
	ATTR_DB_STMT_ABSOLUTE_POSITION = 0x000003E8,    
	ATTR_DB_STMT_ACTIVE_CONNECTION = 0x000003E9,    
	ATTR_DB_STMT_BOF               = 0x000003EA,    
	ATTR_DB_STMT_BOOKMARK          = 0x000003EB,    
	ATTR_DB_STMT_CACHE_SIZE        = 0x000003EC,    
	ATTR_DB_STMT_CURSOR_TYPE       = 0x000003ED,    
	ATTR_DB_STMT_EOF               = 0x000003EE,    
	ATTR_DB_STMT_LOCK_TYPE         = 0x000003F0,    
	ATTR_DB_STMT_MAX_RECORDS       = 0x000003F1,    
	ATTR_DB_STMT_RECORD_COUNT      = 0x000003F2,    
	ATTR_DB_STMT_EDIT_MODE         = 0x00000402,    
	ATTR_DB_STMT_STATUS            = 0x00000405,    
	ATTR_DB_STMT_FILTER            = 0x00000406,    
	ATTR_DB_STMT_ABSOLUTE_PAGE     = 0x00000417,    
	ATTR_DB_STMT_PAGE_SIZE         = 0x00000418,    
	ATTR_DB_STMT_PAGE_COUNT        = 0x0000041A,    
	ATTR_DB_STMT_CURSOR_LOCATION   = 0x0000041B,    
	ATTR_DB_STMT_MARSHAL_OPTIONS   = 0x0000041D,    
	ATTR_DB_STMT_STATE             = 0x0000041E,    
	ATTR_DB_STMT_COMMAND_TIMEOUT   = 0x60030005,
	ATTR_DB_STMT_PREPARED          = 0x60030007,
	ATTR_DB_STMT_COMMAND_TYPE      = 0x6003000C,
	ATTR_DB_STMT_NAME              = 0x6003000E,
	ATTR_DB_STMT_RECORDSET_OBJECT  = 0x00000098,
	ATTR_DB_STMT_COMMAND_OBJECT    = 0x00000099,
	ATTR_DB_STMT_FORCE_TO_FOUR_BYTES = -1
} tDBStatementAttributes;

/* values for the parameter attributes attribute                        */
/* (In ADO, this is the parameter attribute property, so it */
/* became the parameter attributes attribute here)                      */
typedef enum {
	DB_PARAM_SIGNED = 16,
	DB_PARAM_NULLABLE = 64,
	DB_PARAM_LONG = 128,
	DB_PARAM_FORCE_TO_FOUR_BYTES = -1
} tDBParameterAttributes;

/* location of the SQL cursor */
typedef enum {
	DB_CURSOR_LOC_NONE = 1,
	DB_CURSOR_LOC_SERVER = 2,
	DB_CURSOR_LOC_CLIENT = 3,
	DB_CURSOR_LOC_FORCE_TO_FOUR_BYTES = -1
} tDBCursorLoc;

/* possible values of the connection attributes attribute */
typedef enum {
	DB_XACT_COMMIT_RETAINING = 131072,
	DB_XACT_ABORT_RETAINING = 262144,
	DB_XACT_FORCE_TO_FOUR_BYTES = -1
} tDBXactAttribute;

/* isolation level */
typedef enum {
	DB_ISOLATION_LEVEL_UNSPECIFIED = -1,
	DB_ISOLATION_LEVEL_CHAOS = 16,
	DB_ISOLATION_LEVEL_READ_UNCOMMITTED = 256,
	DB_ISOLATION_LEVEL_READ_COMMITTED = 4096,
	DB_ISOLATION_LEVEL_REPEATABLE_READ = 65536,
	DB_ISOLATION_LEVEL_SERIALIZABLE  = 1048576,
	DB_ISOLATION_LEVEL_FORCE_TO_FOUR_BYTES = -1
} tDBIsolationLevel;

/* possible parameter attributes */
typedef enum {
	ATTR_DB_PARAM_VALUE =      0x00000000,
	ATTR_DB_PARAM_NAME =       0x60030000,
	ATTR_DB_PARAM_TYPE =       0x60030004,
	ATTR_DB_PARAM_DIRECTION =  0x60030006,
	ATTR_DB_PARAM_PRECISION =  0x60030008,
	ATTR_DB_PARAM_NUMERIC_SCALE = 0x6003000A,
	ATTR_DB_PARAM_SIZE =       0x6003000C,
	ATTR_DB_PARAM_ATTRIBUTES = 0x6003000F,
	ATTR_DB_PARAM_FORCE_TO_FOUR_BYTES = -1
}tDBParamAttr;

/* possible values for the column attributes attribute */
typedef enum {
	DB_COLUMN_MAY_DEFER = 2,
	DB_COLUMN_UPDATABLE = 4,
	DB_COLUMN_UNKNOWN_UPDATEABLE= 8,
	DB_COLUMN_FIXED = 16,
	DB_COLUMN_IS_NULLABLE = 32,
	DB_COLUMN_MAY_BE_NULL = 64,
	DB_COLUMN_LONG = 128,
	DB_COLUMN_ROW_ID = 256,
	DB_COLUMN_ROW_VERSION = 512,
	DB_COLUMN_CACHE_DEFFERED = 4096,
	DB_COLUMN_FORCE_TO_FOUR_BYTES = -1
}tDBColumnAttributes;

/* possible column attributes */
typedef enum {
	ATTR_DB_COLUMN_VALUE    = 0x00000000,
	ATTR_DB_COLUMN_ATTRIBUTES    = 0x0000040C,
	ATTR_DB_COLUMN_NAME          = 0x0000044C,
	ATTR_DB_COLUMN_TYPE          = 0x0000044E,
	ATTR_DB_COLUMN_DEFINED_SIZE  = 0x0000044F,
	ATTR_DB_COLUMN_ORIGINAL_VALUE= 0x00000450,
	ATTR_DB_COLUMN_UNDERLYING_VALUE=0x00000451,
	ATTR_DB_COLUMN_ACTUAL_SIZE   = 0x00000455,
	ATTR_DB_COLUMN_PRECISION     = 0x60030007,
	ATTR_DB_COLUMN_NUMERIC_SCALE = 0x60030008,
	ATTR_DB_COLUMN_FORCE_TO_FOUR_BYTES = -1
}tDBColumnAttr;

/* Constants for DBInit.  */
#define DB_INIT_SINGLETHREADED  0
#define DB_INIT_MULTITHREADED 1

#define ATTR_DB_MIN 1
#define ATTR_DB_USE_COMMAND 1
#define ATTR_DB_LOCK_TYPE 2
#define ATTR_DB_CURSOR_TYPE 3
#define ATTR_DB_COMMAND_TYPE 4
#define ATTR_DB_DUMMY_PTR 5
#define ATTR_DB_MAX 5

#define DB_FAILED_TO_LOAD_DLL      -100
#define DB_COULD_NOT_FIND_FUNC     -101
#define DB_COULD_NOT_CREATE_MUTEX  -102

/* Error constants */
#define DB_SMALLER_THAN_COLUMN_WIDTH -99        /* not used */
#define DB_ALIAS_NOT_SAVED -98                          /* not used */
#define DB_STMT_NOT_SAVED -98                           /* not used */
#define DB_CONNECTION_NOT_SAVED -97                     /* not used */
#define DB_BETA_EXPIRED -96
#define DB_CANT_FIND_ALIAS -94                          /* not used */
#define DB_CANT_FIND_STMT -94
#define DB_CANT_FIND_CONNECTION -93
#define DB_CANT_DETERMINE_NUM_RECS -92
#define DB_SYNONYM_NOT_SUPPORTED -91
#define DB_UNKNOWN_TABLES_FLAG -90
#define DB_CANT_FIND_MAP -89
#define DB_UNEXPECTED_NULL_PTR -88
#define DB_INVALID_ATTRIBUTE -87
#define DB_INVALID_COLUMN_NUMBER -86
#define DB_UNSUPPORTED_TYPE -85
#define DB_CANT_GET_NATIVE_ERROR -84
#define DB_INVALID_PARAMETER_ATTRIBUTE -83
#define DB_INVALID_COLUMN_ATTRIBUTE -81
#define DB_COLUMN_ATTR_READ_ONLY -80
#define DB_STMT_ATTR_READ_ONLY -79
#define DB_INVALID_STMT_ATTRIBUTE -78
#define DB_INVALID_FOR_COMMAND -77
#define DB_INVALID_FOR_RECORDSET -76
#define DB_REQUIRES_RECORDSET -75
#define DB_REQUIRES_COMMAND -74
#define DB_CONN_ATTR_READ_ONLY -73
#define DB_INVALID_CONN_ATTRIBUTE -72
#define DB_FORMAT_ERROR -71
#define DB_FORMAT_IGNORE_INCOMPAT -70           /* used internally only */
#define DB_FORMAT_IGNORE_NO_DATA_FORMAT -69 /* used internally only */
#define DB_START_REC_TOO_BIG -68
#define DB_FIELD_NUMBER_TOO_BIG -67
#define DB_NOT_ENOUGH_RECORDS -66
#define DB_UNSUPPORTED_SOURCE_TYPE -64
#define DB_NEGATIVE_SIZE -63
#define DB_ALREADY_BOUND -62
#define DB_SINGLE_THREAD_INIT_FAILED -61
#define DB_ILLEGAL_MULTIPLE_MAP_ACTIVATIONS -60
/* These are error codes for the multi-thread critical section stuff */
#define DB_CS_OUT_OF_MEMORY -299
#define DB_CS_INVALID_PARAMETER -298
#define DB_CS_SYSTEM_ERROR -297
#define DB_CS_NOT_INIT_OR_DELETED -296
#define DB_CS_NOT_OWNED -295
#define DB_CS_ALREADY_INIT -294

#define DB_ODBC_ERROR                    -12
#define DB_AUTOMATION_ERROR              -11    /* Error detected by OLE Automation */
#define DB_DBSYS_ERROR           -10    /* Error detected by the underlying     */
					/* database system or driver.           */
#define DB_LOCK_CHANGE_REC       -8      /* Attempt to lock a record and */
		    /* the lock was obtained, but the */
		    /* record has been changed since it */
		    /* was originally read.  This can */
		    /* only occur for DBMSs that require */
		    /* a log file. */
#define DB_LOCK_MULTI_REC        -7      /* Attempt to lock a record and */
		    /* the lock was obtained, but more */
		    /* than one record was locked. This */
		    /* occured because the primary key */
		    /* fields caused more than one */
		    /* record to be selected. */
#define DB_LOCK_NO_REC           -6      /* Attempt to lock a record, but */
		    /* no record in the database was */
		    /* selected by the primary key, */
		    /* the record has been deleted by */
		    /* another user, or another user */
		    /* has changed the value of a */
		    /* key field. */
#define DB_NO_DATA_CHANGE        -9      /* Do not update this column/field */
					 /* Set the status variable of a    */
					 /* bound variable to this value to */
					 /* prevent the column/field from   */
					 /* being updated by DBPutRecord    */
#define DB_LOCK_CHANGE_REC       -8      /* Not used */
#define DB_LOCK_MULTI_REC        -7      /* Not used */
#define DB_LOCK_NO_REC           -6      /* Not used */
#define DB_EOF                   -5      /* No more records to read. */
#define DB_USER_CANCELLED        -4      /* User cancelled out of the logon */
					 /* dialog box. */
#define DB_OUT_OF_MEMORY         -3      /* Insufficient memory for operation. */
#define DB_NULL_DATA             -2      /* Null value.  Returned as the */
					 /* length from a qeDataLen call. */
#define DB_TRUNCATION            -1      /* The buffer passed in to hold */
					 /* a result is not large */
					 /* enough to hold the result. */
					 /* A partial result has been */
					 /* returned in the buffer. */
#define DB_SUCCESS               0       /* Success. */
#define DB_SUCCESS_WITH_INFO     1       /* Success with information (warning). */
#define DB_NO_DATA_WITH_INFO     2       /* EOF with additional information */
					 /* (usually ESC during a fetch). */
#define DB_LIBSYS_ERROR      5           /* Error that occurs when a library */
					 /* can't be loaded. Or when the SLM */
					  /* on the Mac can't be initialized */

#define DB_SRC_AVAILABLE    1

/* type types for DBTables */
#define DB_TBL_TABLE 0x0001
#define DB_TBL_VIEW 0x0002
#define DB_TBL_PROCEDURE 0x0004
#define DB_TBL_SYSTABLE 0x0008
#define DB_TBL_SYNONYM 0x0010
#define DB_TBL_DATABASE 0x0080

#define DB_NO_FLAGS 0x0000
#define DB_UNIQUE_INDEXES 0x0001
#define DB_ACCURATE_STATS 0x0002

#define DB_INDEX_CLUSTERED 1
#define DB_INDEX_HASHED 2
#define DB_INDEX_OTHER 3

#define DB_CASCADE 0
#define DB_RESTRICT 1
#define DB_SET_NULL 2

#ifdef _CVI_
#pragma EnableLibraryRuntimeChecking
#endif

/* connection functions */
extern int SQLFUNC DBConnect(char *connectionString);
extern int SQLFUNC DBSetAttributeDefaultFromParmInfo(int hdbc, int attribute, va_list parmInfo);
extern int SQLCDECL DBSetAttributeDefault(int hdbc, int attribute, ...);
extern int SQLFUNC DBDisconnect(int hdbc);

extern int SQLFUNC DBSetDatabase(int hdbc, char *database);

/* Mapping method functions */
extern int SQLFUNC DBBeginMap(int hdbc);
extern int SQLFUNC DBMapColumnToChar(int mapHandle, char *colName, 
		unsigned long varMaxLen, char *var, long *varStatus, char *fmt);
extern int SQLFUNC DBMapColumnToShort(int mapHandle, char *colName, short *var,
	long *varStatus);
extern int SQLFUNC DBMapColumnToInt(int mapHandle, char *colName, int *var,
	long *varStatus);
extern int SQLFUNC DBMapColumnToFloat(int mapHandle, char *colName,float *var,
	long *varStatus);
extern int SQLFUNC DBMapColumnToDouble(int mapHandle, char *colName, double *var,
	long *varStatus);
extern int SQLFUNC DBMapColumnToBinary(int mapId, char *colName, 
		unsigned long varLen, void *var, long *varStatus);
extern int SQLFUNC DBActivateMap(int mapHandle, char *tableName);
extern int SQLFUNC DBDeactivateMap(int mapHandle);

extern int SQLFUNC DBCreateTableFromMap(int mapHandle, char *tableName);

/* Execute SQL statement */
extern int SQLFUNC DBActivateSQL(int hdbc, char *sqlStatement);
extern int SQLFUNC DBImmediateSQL(int hdbc, char *sqlStatement);

/* Bind Columns method functions */
extern int SQLFUNC DBBindColChar(int hstmt, int colNum, unsigned long stringSize, char *valPtr, long *varStatus, char *fmt);
extern int SQLFUNC DBBindColShort(int hstmt, int colNum, short *valPtr, long *varStatus);
extern int SQLFUNC DBBindColInt(int hstmt, int colNum, int *valPtr, long *varStatus);
extern int SQLFUNC DBBindColFloat(int hstmt, int colNum, float *valPtr, long *varStatus);
extern int SQLFUNC DBBindColDouble(int hstmt, int colNum, double *valPtr, long *varStatus);
extern int SQLFUNC DBBindColBinary(int hstmt, int colNum, 
	unsigned long binSize, void* valPtr, long* varStatus);

/* direct Get and Put functions */
extern int SQLFUNC DBPutColShort(int hstmt, int colNum, short value);
extern int SQLFUNC DBPutColFloat(int hstmt, int colNum, float value);
extern int SQLFUNC DBPutColDouble(int hstmt, int colNum, double value);
extern int SQLFUNC DBPutColInt(int hstmt, int colNum, int value);
extern int SQLFUNC DBPutColChar(int hstmt, int colNum, char *valPtr, 
		char* format);
extern int SQLFUNC DBPutColNull(int hstmt, int colNum);
extern int SQLFUNC DBPutColBinary(int hstmt, int colNum, void* value,
		unsigned int numBytes);
#if ENABLE_VARIANTS		
extern int SQLFUNC DBPutColVariant(int hstmt, int colNum, VARIANT value);
#endif
extern int SQLFUNC DBGetColShort(int hstmt, int colNum, short *value);
extern int SQLFUNC DBGetColInt(int hstmt, int colNum, int* value);
extern int SQLFUNC DBGetColFloat(int hstmt, int colNum, float* value);
extern int SQLFUNC DBGetColDouble(int hstmt, int colNum, double* value);
extern int SQLFUNC DBGetColChar(int hstmt, int colNum, char **valPtr, char* format);
extern int SQLFUNC DBGetColCharBuffer(int hstmt, int colNum, char *buffer,
		int bufferLen, char* format);
extern int SQLFUNC DBGetColBinaryBuffer(int hstmt, int colNum, void* buffer,
		unsigned int bufferLen);
extern int SQLFUNC DBGetColBinary(int hstmt, int colNum, void** value);

#if ENABLE_VARIANTS		
extern int SQLFUNC DBGetColVariant(int hstmt, int colNum, VARIANT* value);
#endif

/* End Execution of SQL statement (whether started with DBActivateMap   */
/* or DBActivateSQL.                                                        */
extern int SQLFUNC DBDeactivateSQL(int hstmt);
/* Fetch Functions */
extern int SQLFUNC DBFetchNext(int hstmt);
extern int SQLFUNC DBFetchPrev(int hstmt);
extern int SQLFUNC DBFetchRandom(int hstmt,long recordNumber);
extern int SQLFUNC DBAllowFetchAnyDirection(int hdbc, int enable);

/* Record operations */
extern int SQLFUNC DBCreateRecord(int hstmt);
extern int SQLFUNC DBDeleteRecord(int hstmt);
extern int SQLFUNC DBPutRecord(int hstmt);
extern int SQLFUNC DBCancelRecordChanges(int hstmt);
extern int SQLFUNC DBUpdateBatch(int hstmt, tDBAffect affectWhichRecords);
/* Information functions */
extern int SQLFUNC DBNumberOfRecords(int hstmt);
extern int SQLFUNC DBNumberOfModifiedRecords(int hstmt);
extern int SQLFUNC DBNumberOfColumns(int hstmt);
extern char * SQLFUNC DBColumnName(int hstmt, int columnNumber);
extern int SQLFUNC DBColumnType(int hstmt, int columnNumber);
extern int SQLFUNC DBColumnWidth(int hstmt, int columnNumber);
/* Transactions */
extern int SQLFUNC DBBeginTran(int hdbc);
extern int SQLFUNC DBCommit(int hdbc);
extern int SQLFUNC DBRollback(int hdbc);

/* Errors/Warnings */
extern int SQLFUNC DBError(void);
extern int SQLFUNC DBWarning(void);
extern int SQLFUNC DBNativeError(void);
extern char * SQLFUNC DBErrorMessage(void);

/* information functions */
extern int SQLFUNC DBSources(int option);
extern int SQLFUNC DBDatabases(int hdbc);
extern int SQLFUNC DBTables(int hdbc, char *qualifier_pattern, char *user_pattern,
	       char *table_pattern, int flags);
extern int SQLFUNC DBIndexes (int hdbc, char *tableName, short flags);
extern int SQLFUNC DBPrimaryKeys (int hdbc, char *tableName);
extern int SQLFUNC DBForeignKeys (int hdbc, char *pkTableName, 
		char *fkTableName);

#if ENABLE_VARIANTS
/* records as an array of variants */
extern int SQLFUNC DBGetVariantArray(int hstmt, VARIANT** theArray,
		unsigned int* numRecs, unsigned int* numFields);
extern int SQLFUNC DBGetVariantArrayValue(VARIANT* theArray,
		unsigned int desiredType, unsigned int numRecs, unsigned int numFields,
	unsigned int recordNum, unsigned int fieldNum, void* dataValue);
extern int SQLFUNC DBGetVariantArrayColumn(VARIANT* theArray, 
		unsigned int numRecs, unsigned int numFields, unsigned int desiredType,
	unsigned int field, unsigned int startRec, int numRecsToFetch, 
	void* dataValues);
extern int SQLFUNC DBFreeVariantArray(VARIANT* theArray, int clearMembers,
		unsigned int numRecs, unsigned int numFields);
extern int SQLFUNC DBOpenSchema(int hdbc, tDBSchemaType schemaType, VARIANT restrictions);
#endif

/* Parameterised commands */
extern int SQLFUNC DBPrepareSQL(int hdbc, char *sqlStatement);
extern int SQLFUNC DBRefreshParams(int hstmt);

extern int SQLFUNC DBCreateParamInt(int hstmt, char *name,
		tDBParameterDirection direction, int value);
extern int SQLFUNC DBCreateParamShort(int hstmt, char *name,
		tDBParameterDirection direction, short value);
extern int SQLFUNC DBCreateParamFloat(int hstmt, char *name,
		tDBParameterDirection direction, float value);
extern int SQLFUNC DBCreateParamDouble(int hstmt, char *name, 
		tDBParameterDirection direction, double value);
extern int SQLFUNC DBCreateParamChar(int hstmt, char *name, 
		tDBParameterDirection direction, char* value, int bufferLen);
extern int SQLFUNC DBCreateParamBinary(int hstmt, char *name,
		tDBParameterDirection direction, void* value, int bufferSize);
		
extern int SQLFUNC DBSetParamInt(int hstmt, int index, int value);
extern int SQLFUNC DBSetParamShort(int hstmt, int index, short value);
extern int SQLFUNC DBSetParamFloat(int hstmt, int index, float value);
extern int SQLFUNC DBSetParamDouble(int hstmt, int index, double value);
extern int SQLFUNC DBSetParamChar(int hstmt, int index, char* value, 
		char* format);
#if ENABLE_VARIANTS		
extern int SQLFUNC DBSetParamVariant(int hstmt, int index, VARIANT value);
#endif
extern int SQLFUNC DBSetParamBinaryBuffer(int hstmt, int index, void* value,
		unsigned int numBytes);
extern int SQLFUNC DBClearParam(int hstmt, int index);

extern int SQLFUNC DBGetParamInt(int hstmt, int index, int* value);
extern int SQLFUNC DBGetParamShort(int hstmt, int index, short* value);
extern int SQLFUNC DBGetParamFloat(int hstmt, int index, float* value);
extern int SQLFUNC DBGetParamDouble(int hstmt, int index, double* value);
extern int SQLFUNC DBGetParamChar(int hstmt, int index, char** value, 
		char* format);
extern int SQLFUNC DBGetParamCharBuffer(int hstmt, int index, char* buffer, 
		int bufferLen, char* format);
#if ENABLE_VARIANTS		
extern int SQLFUNC DBGetParamVariant(int hstmt, int index, VARIANT* value);
#endif
		
extern int SQLFUNC DBGetParamBinary(int hstmt, int index, void** value);
extern int SQLFUNC DBGetParamBinaryBuffer(int hstmt, int index, void* buffer,
		unsigned int bufferLen);
extern int SQLFUNC DBGetParamAttribute(int hstmt, int index, tDBParamAttr attr,
		void* value);
extern int SQLFUNC DBSetParamAttributeFromParmInfo(int hstmt, int index,
		int attribute, va_list parmInfo);
extern int SQLCDECL DBSetParamAttribute (int hstmt, int index, 
		tDBParamAttr attribute, ...);
extern int SQLFUNC DBGetColumnAttribute(int hstmt, int index, 
		tDBColumnAttr attr, void* value);
extern int SQLFUNC DBSetColumnAttributeFromParmInfo(int hstmt, int index,
		int attribute, va_list parmInfo);
extern int SQLCDECL DBSetColumnAttribute (int hstmt, int index, 
		tDBColumnAttr attribute, ...);
extern int SQLFUNC DBExecutePreparedSQL(int hstmt);
extern int SQLFUNC DBClosePreparedSQL(int hstmt);

/* Separate new and open statement.  Required to set statement attributes */
extern int SQLFUNC DBNewSQLStatement(int hdbc, char* sqlStatement);
extern int SQLFUNC DBGetStatementAttribute(int hstmt, 
		tDBStatementAttributes attribute, void *value);
extern int SQLFUNC DBSetStmtAttributeFromParmInfo(int hstmt, long attribute, 
	va_list parmInfo);
extern int SQLCDECL DBSetStatementAttribute(int hstmt, 
		tDBStatementAttributes attribute, ...);
extern int SQLFUNC DBOpenSQLStatement(int hstmt);
extern int SQLFUNC DBMoreResults(int hstmt);
extern int SQLFUNC DBCloseSQLStatement(int hstmt);
extern int SQLFUNC DBDiscardSQLStatement(int hstmt);

/* Separate new and open connection.  Required to set connection attributes */
extern int SQLFUNC DBNewConnection(void);
extern int SQLFUNC DBOpenConnection(int hdbc);
extern int SQLFUNC DBGetConnectionAttribute(int hdbc, 
		tDBConnectionAttr attribute, void *value);
extern int SQLFUNC DBSetConnAttributeFromParmInfo(int hdbc, long attribute, 
	va_list parmInfo);
extern int SQLCDECL DBSetConnectionAttribute(int hdbc, 
		tDBConnectionAttr attribute, ...);
extern int SQLFUNC DBCloseConnection(int hdbc);
extern int SQLFUNC DBDiscardConnection(int hdbc);

/* Version and compatibility functions */
void SQLCDECL DBFree(void *memBlock);
extern int SQLFUNC DBGetSQLToolkitVersion(void);
extern int SQLFUNC DBSetBackwardCompatibility(int version);
extern int SQLFUNC DBInit(int options);

/* These functions translate between active X connection,	*/
/* command and recordset objects and SQL Toolkit connection */
/* and statement handles.  These functions are UNSUPPORTED  */
typedef int          CAObjHandle;
/* Get automation object handles from toolkit handles */
extern int SQLFUNC DBGetCommandObjAndRecordsetObjFromHStmt(int hstmt, 
		int *commandObj, int *recordsetObj);
extern int SQLFUNC DBGetConnectionObjFromHdbc(long hdbc, int* connectionObj);

/* Get toolkit handles from automation object handles.  If the toolkit 	*/
/* handles do not exist, they are created.								*/
extern int SQLFUNC DBConnectionHandleFromConnectionObj(CAObjHandle connectionObj);
extern int SQLFUNC DBStatementHandleFromRecordsetObj(CAObjHandle recordsetObj);
/* For StatementHandleFromCommandObject, if the command does not have a */
/* toolkit handle AND has an associated recordset, you must also supply */
/* the recordset object. OTHERWISE you can pass zero as the recordset. 	*/
extern int SQLFUNC DBStatementHandleFromCommandObj(CAObjHandle commandObj,
		CAObjHandle recordsetObj);

/* Discard toolkit handles.  Use these functions to remove the toolkit  */
/* handles you create for externally supplied connection, command or	*/
/* recordset objects which will be closed and discarded outside the		*/
/* toolkit.  DO NOT call these functions if you use  toolkit functions  */
/* to close or discard the object.										*/
extern int SQLFUNC DBDiscardConnectionHandle(int hdbc);
extern int SQLFUNC DBDiscardStatementHandle(int hstmt);
		
extern void SQLFUNC DBDiscardAllObjects(void);

#ifdef __cplusplus
    }
#endif
#endif
