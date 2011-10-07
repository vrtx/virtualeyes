///////////////////////////////////////////////////////
//
// virtualeyes
//
// @brief   This file defines common debug funcionality including
//          debug logging.
// @author  Ben Becker
// @date    2/3/11
//
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_COMMON_DEBUG_H
#define VIRTUALEYES_COMMON_DEBUG_H

// Includes
#include <QTextStream>
#include <QString>
#include <QDateTime>

// Set default build-time debug output level/lameness cap.  Range is generally 0 to 10, ordered
// from most important to least important (or least lame to most lame).  Entries with a level
// of 10 or above will only be logged to the console.
#ifndef DEBUG_LOG_LAMENESS
#  define DEBUG_LOG_LAMENESS 10
#endif

// Include line numbers in debug output?
#ifndef INCLUDE_LINE_NUMBER
#  define INCLUDE_LINE_NUMBER true
#endif

namespace veyes {

        enum class output_t : uint8_t {
                STDOUT = 0,
                CONSOLE = 1,
                INVALIE = 2
        };

        // Debug log helper
        class debug_log {
        public:
                static void append_prefix(const QString *a_line, quint16 a_lameness);
                static void append_data(QString a_line, quint16 a_lameness);
                static const QString generate_prefix(const char *a_file, qint32 a_line, const char *a_function);
                static output_t c_output;
        };

}

// Macros
#undef VDEBUG
#define VDEBUG(lameness, ...)                                                   \
do {                                                                            \
        if (lameness <= DEBUG_LOG_LAMENESS) {                                   \
                QString prefix_string = debug_log::generate_prefix(__FILE__, __LINE__, __FUNCTION__); \
                veyes::debug_log::append_prefix(&prefix_string, lameness);      \
                QString strdev;                                                 \
                QTextStream out_strm(&strdev);                                  \
                out_strm << __VA_ARGS__;                                        \
                veyes::debug_log::append_data(out_strm.string()->trimmed(), lameness); \
        }                                                                       \
} while (0)

#endif // Include guard
