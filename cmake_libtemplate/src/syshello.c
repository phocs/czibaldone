#include <stdlib.h>
#include <utils.h>

#include <syshello.h>
#include <formatter.h>
#include <sysdeps/sysname.h>

void hello(void) {
	const char *name = sysname();
	char *eman = malloc(strlen(name) + 1);

	if (eman == NULL)
		return;

	memset(eman, '\0', strlen(name) + 1);
	invert_string(eman, name);
	string_lower(eman);
	printf("Hello from %s (%s)\n", name, eman);
}

void hello_version(void) {
	printf("%s %s \n - url: %s\n - include: %s\n - lib: %s\n",
		LIB_NAME, LIB_VERSION, LIB_URL, LIB_INCLUDE_DIR, LIB_DIR);
}
