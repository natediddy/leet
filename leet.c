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

#define L3WHICHTOK(t) \
  ((!alpha_only && !numer_only && !punct_only && !combo_only) || t)

static unsigned char alpha_only = 0;
static unsigned char numer_only = 0;
static unsigned char punct_only = 0;
static unsigned char combo_only = 0;

static const struct
{
  const char letter;
  const char *const *alpha;
  const char *const *numer;
  const char *const *punct;
  const char *const *combo;
} l3tab[26] = {
  {
    'a',
    (const char *const []) {
      "aye", "ci", "Z", NULL
    },
    (const char *const []) {
      "4", NULL
    },
    (const char *const []) {
      "@", "/-\\", "/\\", "^", NULL
    },
    (const char *const []) {
      NULL
    }
  },
  {
    'b',
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "8", "6", "13", NULL
    },
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "|3", "]3", NULL
    }
  },
  {
    'c',
    (const char *const []) {
      "sea", "see", NULL
    },
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "(", "<", "{", NULL
    },
    (const char *const []) {
      NULL
    }
  },
  {
    'd',
    (const char *const []) {
      "cl", NULL
    },
    (const char *const []) {
      "0", NULL
    },
    (const char *const []) {
      "|)", "[)", "])", "I>", "|>", NULL
    },
    (const char *const []) {
      NULL
    }
  },
  {
    'e',
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "3", NULL
    },
    (const char *const []) {
      "&", "[-", NULL
    },
    (const char *const []) {
      NULL
    }
  },
  {
    'f',
    (const char *const []) {
      "ph", NULL
    },
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "|=", "]=", "}", "(=", NULL
    },
    (const char *const []) {
      NULL
    }
  },
  {
    'g',
    (const char *const []) {
      "gee", "jee", "cj", NULL
    },
    (const char *const []) {
      "6", "9", NULL
    },
    (const char *const []) {
      "&", "(_+", "(-", NULL 
    },
    (const char *const []) {
      "C-", "(y,", NULL
    }
  },
  {
    'h',
    (const char *const []) {
      "aych", NULL
    },
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "|-|", "#", "]-[", "[-]", ")-(", "(-)", ":-:", "}{", "}-{", NULL
    },
    (const char *const []) {
      NULL
    }
  },
  {
    'i',
    (const char *const []) {
      "ai", NULL
    },
    (const char *const []) {
      "1", NULL
    },
    (const char *const []) {
      "!", "|", NULL
    },
    (const char *const []) {
      "3y3", NULL
    }
  },
  {
    'j',
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "_|", "_/", "]", "</", "_)", NULL
    },
    (const char *const []) {
      NULL
    }
  },
  {
    'k',
    (const char *const []) {
      "X", NULL
    },
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "|<", "|{", NULL
    },
    (const char *const []) {
      "|X", NULL
    }
  },
  {
    'l',
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "1", "7", NULL
    },
    (const char *const []) {
      "|_", "|", NULL
    },
    (const char *const []) {
      "1J", NULL
    }
  },
  {
    'm',
    (const char *const []) {
      "em", "IYI", "IVI", "nn", "AA", NULL
    },
    (const char *const []) {
      "44", NULL
    },
    (const char *const []) {
      "/\\/\\", "|\\/|", "^^", "//\\\\//\\\\", "(\\/)", "/|\\", "/|/|",
      ".\\\\", "/^^\\", "|^^|", NULL
    },
    (const char *const []) {
      "|v|", "[V]", "(V)", "/V\\", NULL
    }
  },
  {
    'n',
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "|\\|", "/\\/", "//\\\\//", "[\\]", "<\\>", "{\\}", "//", "[]\\[]",
      "]\\[", "~", NULL
    },
    (const char *const []) {
      NULL
    }
  },
  {
    'o',
    (const char *const []) {
      "oh", NULL
    },
    (const char *const []) {
      "0", NULL
    },
    (const char *const []) {
      "()", "[]", NULL
    },
    (const char *const []) {
      NULL
    }
  },
  {
    'p',
    (const char *const []) {
      "q", NULL
    },
    (const char *const []) {
      "9", NULL
    },
    (const char *const []) {
      "|*", "|>", "|\"", "?", NULL
    },
    (const char *const []) {
      "|o", "[]D", "|7", "|D", NULL
    }
  },
  {
    'q',
    (const char *const []) {
      "cue", NULL
    },
    (const char *const []) {
      "9", NULL
    },
    (const char *const []) {
      "(,)", "<|", NULL
    },
    (const char *const []) {
      "0_", "0,", NULL
    }
  },
  {
    'r',
    (const char *const []) {
      "lz", NULL
    },
    (const char *const []) {
      "2", NULL
    },
    (const char *const []) {
      "|^", "|~", "|`", ".-", NULL
    },
    (const char *const []) {
      "|2", "/2", "I2", "[z", "l2", NULL
    }
  },
  {
    's',
    (const char *const []) {
      "z", "es", NULL
    },
    (const char *const []) {
      "5", NULL
    },
    (const char *const []) {
      "$", NULL
    },
    (const char *const []) {
      NULL
    }
  },
  {
    't',
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "7", "1", NULL
    },
    (const char *const []) {
      "+", "-|-", "']['", NULL
    },
    (const char *const []) {
      NULL
    }
  },
  {
    'u',
    (const char *const []) {
      "M", NULL
    },
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "|_|", "(_)", "[_]", "\\_/", "\\_\\", "/_/", NULL
    },
    (const char *const []) {
      "Y3W", NULL
    },
  },
  {
    'v',
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "\\/", "\\\\//", NULL
    },
    (const char *const []) {
      NULL
    }
  },
  {
    'w',
    (const char *const []) {
      "vv", "VV", "UU", "uu", "JL", NULL
    },
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "\\/\\/" "'//", "\\\\'", "\\^/", "\\|/", "\\_|_/", "\\\\//\\\\//",
      "\\_:_/", NULL
    },
    (const char *const []) {
      "(n)", "\\X/", "\\x/", "]I[", NULL
    }
  },
  {
    'x',
    (const char *const []) {
      "ecks", "ex", NULL
    },
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "%", "><", "}{", "*", ")(", NULL
    },
    (const char *const []) {
      NULL
    }
  },
  {
    'y',
    (const char *const []) {
      "j", NULL
    },
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "`/", "`(", "-/", "'/", NULL
    },
    (const char *const []) {
      NULL
    }
  },
  {
    'z',
    (const char *const []) {
      NULL
    },
    (const char *const []) {
      "2", "3", NULL
    },
    (const char *const []) {
      "~/_", "%", NULL
    },
    (const char *const []) {
      "7_", NULL
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
l3tokcnt (int l_index)
{
  int i = 0;

  if (L3WHICHTOK (alpha_only))
    for (; l3tab[l_index].alpha[i] != NULL; ++i)
      ;
  if (L3WHICHTOK (numer_only))
    for (; l3tab[l_index].numer[i] != NULL; ++i)
      ;
  if (L3WHICHTOK (punct_only))
    for (; l3tab[l_index].punct[i] != NULL; ++i)
      ;
  if (L3WHICHTOK (combo_only))
    for (; l3tab[l_index].combo[i] != NULL; ++i)
      ;
  return i;
}

static const char *
l3findtok (int l_index, int t_count)
{
  int i = 0;

  if (L3WHICHTOK (alpha_only))
    for (; l3tab[l_index].alpha[i] != NULL; ++i)
      if (i == t_count)
        return l3tab[l_index].alpha[i];
  if (L3WHICHTOK (numer_only))
    for (; l3tab[l_index].numer[i] != NULL; ++i)
      if (i == t_count)
        return l3tab[l_index].numer[i];
  if (L3WHICHTOK (punct_only))
    for (; l3tab[l_index].punct[i] != NULL; ++i)
      if (i == t_count)
        return l3tab[l_index].punct[i];
  if (L3WHICHTOK (combo_only))
    for (; l3tab[l_index].combo[i] != NULL; ++i)
      if (i == t_count)
        return l3tab[l_index].combo[i];
  return NULL;
}

int
main (int c, char **v)
{
  int i, v_index = 1;

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
                     "  -a, --alpha    Use only alpha tokens\n"
                     "  -n, --numeric  Use only numerical tokens\n"
                     "  -s, --symbols  Use only symbols/punctuation\n"
                     "  -m, --misc     Use only tokens with combinations\n"
                     "  -t, --table    Show table of l337 characters\n"
                     "  -?, -h, --help Show this help message\n"
                     "  -v, --version  Show version information\n", v[0]);
    return EXIT_SUCCESS;
  }
  else if (l3streq (v[1], "-v") || l3streq (v[1], "--version"))
  {
    fputs ("leet 1.1\nNathan Forbes\n", stdout);
    return EXIT_SUCCESS;
  }
  else if (l3streq (v[1], "-t") || l3streq (v[1], "--table"))
  {
    int i;
    for (i = 0; i < 26; ++i)
    {
      fprintf (stdout, "%c:", (char) toupper ((int) l3tab[i].letter));
      int j;
      fputs ("\n  ALPHA: ", stdout);
      for (j = 0; l3tab[i].alpha[j] != NULL; ++j)
      {
        if (j == 0)
          fputs ("  ", stdout);
        fputs (l3tab[i].alpha[j], stdout);
        if (l3tab[i].alpha[j + 1] != NULL)
          fputs ("  ", stdout);
      }
      fputs ("\n  NUMERIC: ", stdout);
      for (j = 0; l3tab[i].numer[j] != NULL; ++j)
      {
        fputs (l3tab[i].numer[j], stdout);
        if (l3tab[i].numer[j + 1] != NULL)
          fputs ("  ", stdout);
      }
      fputs ("\n  SYMBOLS: ", stdout);
      for (j = 0; l3tab[i].punct[j] != NULL; ++j)
      {
        fputs (l3tab[i].punct[j], stdout);
        if (l3tab[i].punct[j + 1] != NULL)
          fputs ("  ", stdout);
      }
      fputs ("\n  MISC: ", stdout);
      for (j = 0; l3tab[i].combo[j] != NULL; ++j)
      {
        if (j == 0)
          fputs ("   ", stdout);
        fputs (l3tab[i].combo[j], stdout);
        if (l3tab[i].combo[j + 1] != NULL)
          fputs ("  ", stdout);
      }
      fputc ('\n', stdout);
    }
    return EXIT_SUCCESS;
  }
  else if (l3streq (v[1], "-a") || l3streq (v[1], "--alpha"))
  {
    alpha_only = 1;
    v_index = 2;
  }
  else if (l3streq (v[1], "-n") || l3streq (v[1], "--numeric"))
  {
    numer_only = 1;
    v_index = 2;
  }
  else if (l3streq (v[1], "-s") || l3streq (v[1], "--symbols"))
  {
    punct_only = 1;
    v_index = 2;
  }
  else if (l3streq (v[1], "-m") || l3streq (v[1], "--misc"))
  {
    combo_only = 1;
    v_index = 2;
  }

  for (i = v_index; v[i]; ++i)
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
          if (ch == l3tab[k].letter)
          {
            int tc = l3tokcnt (k);
            if (tc == 0)
            {
              b[b_index] = ch;
              ++b_index;
              continue;
            }
            int n = l3rand (tc) - 1;
            const char *tok = l3findtok (k, n);
            if (tok && *tok)
            {
              int x, y, ll = strlen (tok);
              for (x = b_index, y = 0; y < ll; ++x, ++y)
                b[x] = tok[y];
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

