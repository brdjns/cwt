/* SPDX-License-Identifier: MIT
   Copyright 2024 Bradley Jones
   Convert between pounds and kilograms.  */

#include <errno.h>
#include <getopt.h>
#include <libgen.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static char const *cmd;
static char const *version = "1.0.0";
static double const factor = 2.2;

static struct option long_opts[] = {
    {"help", no_argument, NULL, 'h'},
    {"version", no_argument, NULL, 'v'},
    {"kg", required_argument, NULL, 'k'},
    {"lb", required_argument, NULL, 'p'},
    {NULL, 0, NULL, 0},
};

static void
errorf(char const *msg)
{
  fprintf(stderr, "%s: %s\n", cmd, msg);
  exit(EXIT_FAILURE);
}

static void
print_usage(FILE *fp)
{
  fprintf(fp, "%s: Usage: %s [-hv] [-k kg] [-p lb]\n", cmd, cmd);
}

static void
print_version(FILE *fp)
{
  fprintf(fp, "%s version %s\n", cmd, version);
}

static void
print_help(void)
{
  print_usage(stdout);
  char *const help = {
      " --help, -h    print this help information\n"
      " --version, -v print version information\n"
      " --kg, -k      weight in kilograms\n"
      " --lb, -p      weight in pounds\n",
  };
  printf("%s", help);
  exit(EXIT_SUCCESS);
}

static double
lb_to_kg(double d)
{
  double kg = d / factor;
  return kg;
}

static double
kg_to_lb(double d)
{
  double lb = d * factor;
  return lb;
}

static double read_number(char *arg)
{
  char *end;
  errno = 0;
  double d = strtod(arg, &end);

  if (arg == end)
    errorf("invalid weight");
  if (*end != '\0')
    errorf("extra characters after weight");
  if (errno == ERANGE)
    errorf("weight out of range");
  if (isnan(d) || isinf(d) || d <= 0.0)
    errorf("invalid weight");
  return d;
}

int
main(int argc, char **argv)
{
  int o;
  cmd = basename(argv[0]);

  if (argc < 2) {
    print_usage(stderr);
    exit(EXIT_FAILURE);
  }

  while ((o = getopt_long(argc, argv, "k:p:hv", long_opts, NULL)) != -1) {
    switch (o) {
    case 'h':
      print_help();
      break;
    case 'k':
      printf("%.2f lb\n", kg_to_lb(read_number(optarg)));
      break;
    case 'p':
      printf("%.2f kg\n", lb_to_kg(read_number(optarg)));
      break;
    case 'v':
      print_version(stdout);
      break;
    default:
      print_usage(stderr);
      exit(EXIT_FAILURE);
    }
  }
  exit(EXIT_SUCCESS);
}
