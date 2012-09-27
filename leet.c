/*
 * leet.c
 *
 * Copyright (c) 2012, Nathan Forbes
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of the FreeBSD Project.
 *
 * This is an alpha to "l337" speak translator, useful for
 * generating strong passwords and such.
 *
 * NOTE: this program only deals with ASCII characters
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static const struct
{
  const char alpha;
  const char *const *leet;
} l3tab[26] = {
  {
    'a',
    (const char *const [])
    {
      "4", "@", "/-\\", "/\\", "^", "aye", "ci", "Z", NULL
    }
  },
  {
    'b',
    (const char *const [])
    {
      "8", "|3", "6", "13", "|3", "]3", NULL
    }
  },
  {
    'c',
    (const char *const [])
    {
      "(", "<", "{", "sea", "see", NULL
    }
  },
  {
    'd',
    (const char *const [])
    {
      "|)", "[)", "])", "I>", "|>", "0", "cl", NULL
    }
  },
  {
    'e',
    (const char *const [])
    {
      "3", "&", "[-", NULL
    }
  },
  {
    'f',
    (const char *const [])
    {
      "|=", "]=", "}", "ph", "(=", NULL
    }
  },
  {
    'g',
    (const char *const [])
    {
      "6", "9", "&", "(_+", "C-", "gee", "jee", "(y,", "cj", NULL
    }
  },
  {
    'h',
    (const char *const [])
    {
      "|-|", "#", "]-[", "[-]", ")-(", "(-)", ":-:", "}{", "}-{", "aych", NULL
    }
  },
  {
    'i',
    (const char *const [])
    {
      "!", "1", "|", "eye", "3y3", "ai", NULL
    }
  },
  {
    'j',
    (const char *const [])
    {
      "_|", "_/", "]", "</", "_)", NULL
    }
  },
  {
    'k',
    (const char *const [])
    {
      "X", "|<", "|X", "|{", NULL
    }
  },
  {
    'l',
    (const char *const [])
    {
      "1", "7", "|_", "|", "1J", NULL
    }
  },
  {
    'm',
    (const char *const [])
    {
      "44", "/\\/\\", "|\\/|", "em", "|v|", "IYI", "IVI", "[V]", "^^", "nn",
      "//\\\\//\\\\", "(V)", "(\\/)", "/|\\", "/|/|", ".\\\\", "/^^\\",
      "/V\\", "|^^|", "AA", NULL
    }
  },
  {
    'n',
    (const char *const [])
    {
      "|\\|", "/\\/", "//\\\\//", "[\\]", "<\\>", "{\\}", "//", "[]\\[]",
      "]\\[", "~", NULL
    }
  },
  {
    'o',
    (const char *const [])
    {
      "0", "()", "oh", "[]", NULL
    }
  },
  {
    'p',
    (const char *const [])
    {
      "|*", "|o", "|>", "|\"", "?", "9", "[]D", "|7", "q", "|D", NULL
    }
  },
  {
    'q',
    (const char *const [])
    {
      "0_", "0,", "(,)", "<|", "cue", "9", NULL
    }
  },
  {
    'r',
    (const char *const [])
    {
      "|2", "2", "/2", "I2", "|^", "|~", "lz", "[z", "|`", "l2", ".-", NULL
    }
  },
  {
    's',
    (const char *const [])
    {
      "5", "$", "z", "es", NULL
    }
  },
  {
    't',
    (const char *const [])
    {
      "7", "+", "-|-", "1", "']['", NULL
    }
  },
  {
    'u',
    (const char *const [])
    {
      "|_|", "(_)", "Y3W", "M", "[_]", "\\_/", "\\_\\", "/_/", NULL
    }
  },
  {
    'v',
    (const char *const [])
    {
      "\\/", "\\\\//", NULL
    }
  },
  {
    'w',
    (const char *const [])
    {
      "\\/\\/", "vv", "VV", "'//", "\\\\'", "\\^/", "(n)", "\\X/", "\\x/",
      "\\|/", "\\_|_/", "\\\\//\\\\//", "\\_:_/", "]I[", "UU", "uu", "JL",
      NULL
    }
  },
  {
    'x',
    (const char *const [])
    {
      "%", "><", "}{", "ecks", "*", ")(", "ex", NULL
    }
  },
  {
    'y',
    (const char *const [])
    {
      "j", "`/", "`(", "-/", "'/", NULL
    }
  },
  {
    'z',
    (const char *const [])
    {
      "2", "~/_", "%", "3", "7_", NULL
    }
  }
};

static unsigned char
l3streq (const char *s1, const char *s2)
{
  if ((s1 && *s1) && (s2 && *s2))
  {
    int l = strlen (s2);
    if ((strlen (s1) == l) && (strncmp (s1, s2, l) == 0))
      return 1;
  }
  return 0;
}

static int
l3rand (int max)
{
  time_t s;

  time (&s);
  srand ((unsigned int) s);
  return (rand () % max + 1);
}

static int
l3symcount (const char ch)
{
  int i;

  for (i = 0; i < 26; ++i)
  {
    if (ch == l3tab[i].alpha)
    {
      int j;
      for (j = 0; l3tab[i].leet[j] != NULL; ++j)
        ;
      return j;
    }
  }
  return 0;
}

int
main (int c, char **v)
{
  int i;

  if (c == 1)
  {
    fprintf (stderr, "usage: %s STRING ...\n", v[0]);
    return EXIT_FAILURE;
  }

  if (l3streq (v[1], "-?") ||
      l3streq (v[1], "-h") ||
      l3streq (v[1], "--help"))
  {
    fprintf (stdout, "Usage: %s STRING ...\n"
                     "Options:\n"
                     "  -t, --table    Show table of l337 characters\n"
                     "  -?, -h, --help Show this help message\n"
                     "  -v, --version  Show version information\n", v[0]);
    return EXIT_SUCCESS;
  }
  else if (l3streq (v[1], "-v") || l3streq (v[1], "--version"))
  {
    fputs ("Leeter 1.0\nNathan Forbes\n", stdout);
    return EXIT_SUCCESS;
  }
  else if (l3streq (v[1], "-t") || l3streq (v[1], "--table"))
  {
    int i;
    for (i = 0; i < 26; ++i)
    {
      fprintf (stdout, "%c:\n  ", (char) toupper ((int) l3tab[i].alpha));
      int j;
      for (j = 0; l3tab[i].leet[j] != NULL; ++j)
      {
        fputs (l3tab[i].leet[j], stdout);
        if (l3tab[i].leet[j + 1] != NULL)
          fputs ("  ", stdout);
      }
      fputc ('\n', stdout);
    }
    return EXIT_SUCCESS;
  }

  for (i = 1; v[i]; ++i)
  {
    int j, l = strlen (v[i]) * 3, b_index = 0;
    char b[l];
    for (j = 0; v[i][j]; ++j)
    {
      if (isalpha (v[i][j]))
      {
        int k;
        for (k = 0; k < 26; ++k)
        {
          char ch = (char) tolower ((int) v[i][j]);
          if (ch == l3tab[k].alpha)
          {
            int n = l3rand (l3symcount (ch)) - 1;
            if (l3tab[k].leet[n])
            {
              int x, y, ll = strlen (l3tab[k].leet[n]);
              for (x = b_index, y = 0; y < ll; ++x, ++y)
                b[x] = l3tab[k].leet[n][y];
              b_index += ll;
            }
          }
        }
      }
      else
      {
        b[b_index] = v[i][j];
        b_index += 1;
      }
    }
    b[b_index] = '\0';
    if (*b)
      fprintf (stdout, "%s: %s\n", v[i], b);
    else
      fprintf (stderr, "%s: error: could not convert '%s'\n", v[0], v[i]);
  }
  return EXIT_SUCCESS;
}

