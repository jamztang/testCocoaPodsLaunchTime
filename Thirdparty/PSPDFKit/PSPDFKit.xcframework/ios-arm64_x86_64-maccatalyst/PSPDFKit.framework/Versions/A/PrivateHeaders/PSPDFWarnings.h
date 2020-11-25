//
//  Copyright © 2012-2020 PSPDFKit GmbH. All rights reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE PSPDFKIT LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#pragma once

// Normally the compiler expects all enum values to be set since -Wswitch-enum is enabled.
// This exception is for enums where we on purpose only process a small part.
#define PSPDF_SWITCH_NOWARN(expression) _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wswitch-enum\"") switch (expression) _Pragma("clang diagnostic pop")

// Sometimes we do bad things like casting a void * to an integer.
// This is most likely some use of Core Foundation array classes.
// This macro wraps the assignment to hide the warning.
#define PSPDF_BAD_FUNCTION_CAST(expression) _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wbad-function-cast\"") expression _Pragma("clang diagnostic pop")

#define PSPDF_SILENCE_CALL_TO_UNKNOWN_SELECTOR(expression) _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Warc-performSelector-leaks\"") expression _Pragma("clang diagnostic pop")

#define PSPDF_UNUSED_GETTER_RETURN_VALUE(expression) _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wunused-getter-return-value\"") expression _Pragma("clang diagnostic pop")

#define PSPDF_IGNORE_NONNULL(expression) _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wnonnull\"") expression _Pragma("clang diagnostic pop")

#define PSPDF_IGNORE_NULLABLE_CONVERSION(expression) _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wnullable-to-nonnull-conversion\"") expression _Pragma("clang diagnostic pop")

#define PSPDF_ALLOW_CAST_QUALIFIERS(expression) _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wcast-qual\"") expression _Pragma("clang diagnostic pop")

#define PSPDF_IGNORE_RESERVED_MACRO(expression) _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wreserved-id-macro\"") expression _Pragma("clang diagnostic pop")

#define PSPDF_IGNORE_EXIT_TIME_DESTRUCTOR(expression) _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wexit-time-destructors\"") _Pragma("clang diagnostic ignored \"-Wglobal-constructors\"") expression _Pragma("clang diagnostic pop")

// Use __c11_atomic_exchange/__c11_atomic_load for performance critical sections.
// Ignore the warning for debugging code.
#define PSPDF_IGNORE_IMPLICIT_SQL_CST_ATOMIC(expression) _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Watomic-implicit-seq-cst\"") expression _Pragma("clang diagnostic pop")

// When using PSPDFClass(), we’re losing type information for the compiler:
// a fairly specific class becomes an arbitrary one, which could — in theory — lead to incorrect code–generation when several classes implement the same selector using differing ownership regarding their parameters/return values.
// Since we use PSPDFClass() in contexts without such overloading, it is handy — and safe to disable this warning there.
#define PSPDF_NON_STRICT_SELECTOR(expression) _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wstrict-selector-match\"") expression _Pragma("clang diagnostic pop")

#define PSPDF_UNDECLARED_SELECTOR(expression) _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wundeclared-selector\"") expression _Pragma("clang diagnostic pop")

#define PSPDF_DEPRECATED_DECLARATIONS_BEGIN _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
#define PSPDF_DEPRECATED_DECLARATIONS_END _Pragma("clang diagnostic pop")

#define PSPDF_DEPRECATED_IMPLEMENTATIONS_BEGIN _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wdeprecated-implementations\"")

#define PSPDF_DEPRECATED_IMPLEMENTATIONS_END _Pragma("clang diagnostic pop")
