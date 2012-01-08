///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the debug logging system
// @author  ben
// @date    7/16/2011
///////////////////////////////////////////////////////


#include "debug.hpp"
#include "main_view.hpp"
#include "console_widget.hpp"

using namespace veyes;
using namespace std;

int debug_log::c_output = output_t::CONSOLE;

void debug_log::append_prefix(const QString *a_line, quint16 a_lameness)
{
        global <main_view> g_window;
        if (c_output == output_t::STDOUT ||
            a_lameness >= 10 ||
            !g_window.is_valid() ||
            !g_window->m_console_widget.is_valid()) {
                // std output specified, or output is unimportant (lame)
                cout << a_line->toStdString();
                cout.flush();
        } else if (c_output == output_t::CONSOLE) {
                global <main_view> g_window;
                g_window->m_console_widget->append(*a_line, text_format_t::BACKGROUND | text_format_t::PARTIAL, a_lameness);
        }
}

void debug_log::append_data(QString a_line, quint16 a_lameness)
{
        global <main_view> g_window;
        if (c_output == output_t::STDOUT ||
            a_lameness >= 10 ||
            !g_window.is_valid() ||
            !g_window->m_console_widget.is_valid()) {
                // std output specified, output is lame, or console is unavailable
                cout << a_line.toStdString() << endl;
        } else if (c_output == output_t::CONSOLE) {
                g_window->m_console_widget->append(a_line, text_format_t::DEBUG, a_lameness);
        }
}

const QString debug_log::generate_prefix(const char *a_file, qint32 a_line, const char *a_function)
{
        QString prefixdev;
        QTextStream prefix_strm(&prefixdev);
        prefix_strm << "[";
        prefix_strm.setPadChar(' ');
        prefix_strm.setFieldWidth(18);
        prefix_strm.setFieldAlignment(QTextStream::AlignLeft);
        prefix_strm << QDateTime::currentDateTime().toString("h:mm:ss.zzz ap");
        prefix_strm.setFieldWidth(1);
        prefix_strm << " ";
        prefix_strm.setPadChar(' ');
        prefix_strm.setFieldWidth(20);
        prefix_strm.setFieldAlignment(QTextStream::AlignLeft);
        prefix_strm << QString((strrchr(a_file, '/') ? strrchr(a_file, '/') : a_file - 1) + 1);
        prefix_strm.setFieldWidth(1);
        prefix_strm << " ";
        prefix_strm.setPadChar(' ');
        prefix_strm.setFieldWidth(16);
        prefix_strm.setFieldAlignment(QTextStream::AlignLeft);
        prefix_strm << QString(a_function).append("()");
        if (INCLUDE_LINE_NUMBER) {
                prefix_strm.setFieldWidth(3);
                prefix_strm << " @L";
                prefix_strm.setPadChar(' ');
                prefix_strm.reset();
                prefix_strm.setFieldAlignment(QTextStream::AlignLeft);
                prefix_strm.setFieldWidth(3);
                prefix_strm << a_line;
        }
        prefix_strm.setFieldAlignment(QTextStream::AlignLeft);
        prefix_strm.setFieldWidth(3);
        prefix_strm << "]: ";
        return *prefix_strm.string();
}
