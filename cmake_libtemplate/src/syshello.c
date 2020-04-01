#include <utils.h>
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
