#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstdarg>

using namespace std;

FILE* fp_in = 0;
FILE* fp_out = 0;

string in_file = "";
string out_file = "";
string var_name = "";

void out(const char* fmt, ...) {
   char buf[1024];
   va_list ap;
   va_start(ap, fmt);
   vsnprintf(buf, sizeof(buf), fmt, ap);
   va_end(ap);
   fprintf(fp_out, "%s", buf);
}

void write_file_header(const char* include_guard) {
    out("#ifndef %s\n", include_guard);
    out("#define %s\n", include_guard);
}

void write_file_footer(const char* include_guard) {
    out("#endif /* %s */\n", include_guard);
}

void make_c_string(string & in) {
    string out;
    for (size_t i = 0; i < in.size(); ++i) {
        char c = in[i];
        if ('"' == c) {
            out += "\\\"";
        } else if ('\\' == c) {
            out += "\\\\";
        } else {
            out += c;
        }
    }
    in = out;
}

void write_var_header() {
    out("const char* %s =\n", var_name.c_str());
}

void write_var_footer() {
    out(";\n");
}

void write_line(const string & line) {
    out("\"%s\\n\"\n", line.c_str());
}

void strtoupper(char* str) {
    while(*str != '\0') {
        *str = toupper((unsigned char) *str);
        str++;
    }
}

size_t strlstchar(const char *str, const char ch) {
    return strrchr(str, ch) - str;
}

int main(int argc, char** args) {
    if (argc != 4) {
        printf("Usage: %s var_name in_file out_file\n", args[0]);
        return EXIT_FAILURE;
    }
    var_name = args[1];
    in_file = args[2];
    out_file = args[3];

    fp_in = fopen(in_file.c_str(), "rt");
    if (fp_in) {
        fp_out = fopen(out_file.c_str(), "wt");
        if (fp_out) {
            const char* out_file_name = strrchr(out_file.c_str(), '/');
            if (out_file_name) {
                out_file_name++;
            } else {
                out_file_name = out_file.c_str();
            }
            char* include_guard = new char[strlen(out_file_name) + 1];
            strcpy(include_guard, out_file_name);
            strtoupper(include_guard);
            int last_index_of_dot = strlstchar(include_guard, '.');
            if (last_index_of_dot >= 0) {
                *(include_guard + last_index_of_dot) = '_';
            }

            write_file_header(include_guard);
            out("\n");
            write_var_header();
            char buf[1024];
            while (fgets(buf, sizeof(buf), fp_in)) {
                string s(buf);
                s = s.substr(0, s.find('\n'));
                make_c_string(s);
                write_line(s);
            }
            write_var_footer();
            out("\n");
            write_file_footer(include_guard);
            fclose(fp_out);

            delete[] include_guard;
        } else {
            printf("error opening %s\n", out_file.c_str());
            return EXIT_FAILURE;
        }
        fclose(fp_in);
    } else {
        printf("error opening %s\n", in_file.c_str());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
