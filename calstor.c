#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TRUE 1
#define FALSE !TRUE

typedef unsigned long long ull;

char *units[] = {
	"b",
	"kib",
	"mib",
	"gib",
	"tib",
	"kb",
	"mb",
	"gb",
	"tb",
};

void printval(double val, char *unit)
{
	if (trunc(val) == val)
		printf("%40llu %s\n", (ull)val, unit);
	else
		printf("%40.10f %s\n", val, unit);
}

ull convertbyte(char *buf)
{
	/* Convert and print in bytes */
	ull bytes = strtoull(buf, NULL, 0);
	printf("%40llu B\n\n", bytes);

	printf("                 IEC standard\n                 ------------\n\n");
	/* Convert and print in IEC standard units */
	double val = bytes / (double)1024;
	printval(val, "KiB");

	val = bytes / (double)(1 << 20);
	printval(val, "MiB");

	val = bytes / (double)(1 << 30);
	printval(val, "GiB");

	val = bytes / (double)((ull)1 << 40);
	printval(val, "TiB");

	/* Convert and print in SI standard values */
	printf("\n                 SI standard\n                 -----------\n\n");
	val = bytes / (double)1000;
	printval(val, "kB");

	val = bytes / (double)1000000;
	printval(val, "MB");

	val = bytes / (double)1000000000;
	printval(val, "GB");

	val = bytes / (double)1000000000000;
	printval(val, "TB");

	return bytes;
}

ull convertkib(char *buf)
{
	double kib = strtod(buf, NULL);

	/* Convert and print in bytes */
	ull bytes = (ull)(kib * 1024);
	printf("%40llu B\n\n", bytes);

	printf("                 IEC standard\n                 ------------\n\n");
	printval(kib, "KiB");

	double val = kib / 1024;
	printval(val, "MiB");

	val = kib / (1 << 20);
	printval(val, "GiB");

	val = kib / (1 << 30);
	printval(val, "TiB");

	printf("\n                 SI standard\n                 -----------\n\n");
	val = kib * 1024 / 1000;
	printval(val, "kB");

	val = kib * 1024 / 1000000;
	printval(val, "MB");

	val = kib * 1024 / 1000000000;
	printval(val, "GB");

	val = kib * 1024 / 1000000000000;
	printval(val, "TB");

	return bytes;
}

ull convertmib(char *buf)
{
	double mib = strtod(buf, NULL);

	/* Convert and print in bytes */
	ull bytes = (ull)(mib * (1 << 20));
	printf("%40llu B\n\n", bytes);

	printf("                 IEC standard\n                 ------------\n\n");
	double val = mib * 1024;
	printval(val, "KiB");

	printval(mib, "MiB");

	val = mib / 1024;
	printval(val, "GiB");

	val = mib / (1 << 20);
	printval(val, "TiB");

	printf("\n                 SI standard\n                 -----------\n\n");
	val = mib * (1 << 20)/ 1000;
	printval(val, "kB");

	val = mib * (1 << 20) / 1000000;
	printval(val, "MB");

	val = mib * (1 << 20) / 1000000000;
	printval(val, "GB");

	val = mib * (1 << 20) / 1000000000000;
	printval(val, "TB");

	return bytes;
}

ull convertgib(char *buf)
{
	double gib = strtod(buf, NULL);

	/* Convert and print in bytes */
	ull bytes = (ull)(gib * (1 << 30));
	printf("%40llu B\n\n", bytes);

	printf("                 IEC standard\n                 ------------\n\n");
	double val = gib * (1 << 20);
	printval(val, "KiB");

	val = gib * 1024;
	printval(val, "MiB");

	printval(gib, "GiB");

	val = gib / 1024;
	printval(val, "TiB");

	printf("\n                 SI standard\n                 -----------\n\n");
	val = gib * (1 << 30)/ 1000;
	printval(val, "kB");

	val = gib * (1 << 30) / 1000000;
	printval(val, "MB");

	val = gib * (1 << 30) / 1000000000;
	printval(val, "GB");

	val = gib * (1 << 30) / 1000000000000;
	printval(val, "TB");

	return bytes;
}

ull converttib(char *buf)
{
	double tib = strtod(buf, NULL);

	/* Convert and print in bytes */
	ull bytes = (ull)(tib * ((ull)1 << 40));
	printf("%40llu B\n\n", bytes);

	printf("                 IEC standard\n                 ------------\n\n");
	double val = tib * (1 << 30);
	printval(val, "KiB");

	val = tib * (1 << 20);
	printval(val, "MiB");

	val = tib * 1024;
	printval(val, "GiB");

	printval(tib, "TiB");

	printf("\n                 SI standard\n                 -----------\n\n");
	val = tib * ((ull)1 << 40)/ 1000;
	printval(val, "kB");

	val = tib * ((ull)1 << 40) / 1000000;
	printval(val, "MB");

	val = tib * ((ull)1 << 40) / 1000000000;
	printval(val, "GB");

	val = tib * ((ull)1 << 40) / 1000000000000;
	printval(val, "TB");

	return bytes;
}

char *strtolower(char *buf)
{
	char *p = buf;

	for (; *p; ++p)
		*p = tolower(*p);

	return buf;
}

int main(int argc, char **argv)
{
	int opt = 0;

	opterr = 0;

	while ((opt = getopt (argc, argv, "cs:")) != -1) {
		switch (opt) {
		case 'c':
			break;
		case 's':
			break;
		default:
			if (isprint (optopt))
				fprintf(stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf(stderr, "Unknown option\n");

			return 1;
		}
	}

	printf("Non-option args: %d\n", argc - optind);

	if (argc - optind == 2) {
		int ret = 0;
		int count = sizeof(units)/sizeof(*units);
		ull bytes = 0;

		while (count-- > 0) {
			ret = strcmp(units[count], strtolower(argv[optind + 1]));
			if (!ret)
                                break;
		}

		if (count == -1) {
			fprintf(stderr, "No matching unit\n");
			return 1;
		}

		printf("count: %x unit: %s\n", count, units[count]);

		switch (count) {
		case 0:
			bytes = convertbyte(argv[optind]);
			break;
		case 1:
			bytes = convertkib(argv[optind]);
			break;
		case 2:
			bytes = convertmib(argv[optind]);
			break;
		case 3:
			bytes = convertgib(argv[optind]);
			break;
		case 4:
			bytes = converttib(argv[optind]);
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		default:
			fprintf(stderr, "Unknown unit\n");
			return 1;
		}

		printf("\n\nADDRESS: %llu, 0x%llx\n", bytes, bytes);
		printf("LBA: %llu, 0x%llx OFFSET: %llu, 0x%llx\n", bytes >> 9, bytes >> 9, bytes % 512, bytes % 512);
	}

	return 0;
}