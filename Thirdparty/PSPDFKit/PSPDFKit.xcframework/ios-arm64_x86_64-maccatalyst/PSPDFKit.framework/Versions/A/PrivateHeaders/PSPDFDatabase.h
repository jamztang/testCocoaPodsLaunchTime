//
//  PSPDFDatabase.h
//  PSPDFKit
//
//  This is modified 3rd-party code licensed under MIT.
//
//  Copyright © 2008 Flying Meat Inc.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#if !defined(PSPDF_STATIC_BUILD)
#import <PSPDFKit/PSPDFEnvironment.h>
#else
#import "PSPDFEnvironment.h"
#endif

@class PSPDFResultSet, PSPDFStatement;
@protocol PSPDFDatabaseEncryptionProvider;

NS_ASSUME_NONNULL_BEGIN
// Abstraction for the SQLite 3 database.
@interface PSPDFDatabase : NSObject

// Config
@property (atomic) BOOL traceExecution;
@property (atomic) BOOL checkedOut;
@property (atomic) int busyRetryTimeout;
@property (atomic) BOOL crashOnErrors;
@property (atomic) BOOL logsErrors;
@property (atomic, retain, nullable) NSMutableDictionary<NSString *, PSPDFStatement *> *cachedStatements;
@property (atomic, readonly, nullable) id<PSPDFDatabaseEncryptionProvider> databaseEncryptionProvider;

// Initializer
+ (instancetype)databaseWithPath:(nullable NSString *)inPath databaseEncryptionProvider:(nullable id<PSPDFDatabaseEncryptionProvider>)databaseEncryptionProvider;
- (instancetype)initWithPath:(nullable NSString *)inPath databaseEncryptionProvider:(nullable id<PSPDFDatabaseEncryptionProvider>)databaseEncryptionProvider;

- (BOOL)open;
- (BOOL)openWithFlags:(int)flags;
- (BOOL)close;
- (BOOL)goodConnection;
- (void)clearCachedStatements;
- (void)closeOpenResultSets;
- (BOOL)hasOpenResultSets;

- (nullable NSString *)databasePath;

- (nullable NSString *)lastErrorMessage;

- (int)lastErrorCode;
- (BOOL)hadError;
- (nullable NSError*)lastError;

- (BOOL)executeUpdate:(NSString *)sql withErrorAndBindings:(NSError **)outErr, ...;
- (BOOL)executeUpdate:(NSString *)sql, ...;
- (BOOL)executeUpdateWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
- (BOOL)executeUpdate:(NSString *)sql withArgumentsInArray:(nullable NSArray *)arguments;
- (BOOL)executeUpdate:(NSString *)sql withParameterDictionary:(nullable NSDictionary *)arguments;

- (nullable PSPDFResultSet *)executeQuery:(NSString *)sql, ...;
- (nullable PSPDFResultSet *)executeQueryWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(1,2);
- (nullable PSPDFResultSet *)executeQuery:(NSString *)sql withArgumentsInArray:(nullable NSArray *)arguments;
- (nullable PSPDFResultSet *)executeQuery:(NSString *)sql withParameterDictionary:(nullable NSDictionary *)arguments;

- (BOOL)rollback;
- (BOOL)commit;
- (BOOL)beginTransaction;
- (BOOL)beginDeferredTransaction;
- (BOOL)inTransaction;
@property (nonatomic) BOOL shouldCacheStatements;

/// WAL journaling is faster. http://www.sqlite.org/wal.html
- (void)enableWALJournal;

/// Allow 2MB of cache (default is 2000 pages)
- (void)enableLowMemoryMode;

/// Flush all caches to disk.
- (void)shrinkMemory;

- (BOOL)startSavePointWithName:(NSString *)name error:(NSError **)outErr;
- (BOOL)releaseSavePointWithName:(NSString *)name error:(NSError **)outErr;
- (BOOL)rollbackToSavePointWithName:(NSString *)name error:(NSError **)outErr;
- (nullable NSError*)inSavePoint:(void (^)(BOOL *rollback))block;

+ (BOOL)isSQLiteThreadSafe;
+ (NSString *)sqliteLibVersion;

- (int)changes;

/** Generate an `NSDateFormat` that won't be broken by timezone or locale changes.

 Use this method to generate values to set the dateFormat property.

 @param format A valid `NSDateFormatter` format string.

 Example:

 `myDB.dateFormat = [PSPDFDatabase storeableDateFormat:@"yyyy-MM-dd HH:mm:ss"];`

 Note that `NSDateFormatter` is not thread-safe, so the formatter generated by this method should be assigned to only one PSPDF instance and should not be used for other purposes.

 */
+ (NSDateFormatter *)storeableDateFormat:(nullable NSString *)format;


/** Test whether the database has a date formatter assigned.

 */
- (BOOL)hasDateFormatter;


/** Set to a date formatter to use string dates with sqlite instead of the default UNIX timestamps.

 Set to nil to use UNIX timestamps.

 Defaults to nil.

 Should be set using a formatter generated using `PSPDFDatabase::storeableDateFormat`.

 Note there is no direct getter for the `NSDateFormatter`, and you should not use the formatter you pass to PSPDF for other purposes, as `NSDateFormatter` is not thread-safe.

 */
- (void)setDateFormat:(nullable NSDateFormatter *)format;


/** Convert the supplied `NSString` to `NSDate`, using the current database formatter.

 Returns nil if no formatter is set.

 */
- (nullable NSDate *)dateFromString:(nullable NSString *)s;

/** Convert the supplied `NSDate` to `NSString`, using the current database formatter.

 Returns nil if no formatter is set.

 */
- (nullable NSString *)stringFromDate:(nullable NSDate *)date;

@end

// Before using any encryption methods, you must register an `PSPDFDatabaseEncryptionProvider` implementation
// with the `PSPDFKit` class.
@interface PSPDFDatabase (EncryptionSupport)

- (BOOL)openWithEncryptionKey:(nullable NSData *)key;
- (BOOL)setKeyData:(nullable NSData *)keyData;
- (BOOL)rekey:(nullable NSData *)keyData;

@end
NS_ASSUME_NONNULL_END

#define PSPDFCheckedUpdate(db, expression, ...) \
do { if (![db executeUpdate:expression, ##__VA_ARGS__]) { \
PSPDFLogError(@"Failed to perform update: %@", db.lastErrorMessage); \
}} while(0)

// Checks if update completes and sets `rollback` to YES if it failed.
#define PSPDFCheckedUpdateWithRollback(db, rollback, expression, ...) \
do { if (![db executeUpdate:expression, ##__VA_ARGS__]) { \
PSPDFLogError(@"Failed to perform update: %@", db.lastErrorMessage); \
if (rollback) *(volatile BOOL *)rollback = YES; \
}} while(0)