#define PM9SCREW        "\tPM9SCREW\t"
#define PM9SCREW_LEN     10

#include "Zend/zend_hash.h"
extern zend_module_entry php_screw_module_entry;
#define screw_module_ptr &php_screw_module_entry
#define phpext_screw_ptr screw_module_ptr

char *zdecode(char *inbuf, int inbuf_len, int *resultbuf_len);
char *zencode(char *inbuf, int inbuf_len, int *resultbuf_len);
