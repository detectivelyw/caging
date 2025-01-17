/* DO NOT EDIT! GENERATED AUTOMATICALLY! */
/* A GNU-like <dirent.h>.
   Copyright (C) 2006-2009 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef _GL_DIRENT_H

#if __GNUC__ >= 3
#pragma GCC system_header
#endif

/* The include_next requires a split double-inclusion guard.  */
#include_next <dirent.h>

#ifndef _GL_DIRENT_H
#define _GL_DIRENT_H

/* The definition of GL_LINK_WARNING is copied here.  */
/* GL_LINK_WARNING("literal string") arranges to emit the literal string as
   a linker warning on most glibc systems.
   We use a linker warning rather than a preprocessor warning, because
   #warning cannot be used inside macros.  */
#ifndef GL_LINK_WARNING
  /* This works on platforms with GNU ld and ELF object format.
     Testing __GLIBC__ is sufficient for asserting that GNU ld is in use.
     Testing __ELF__ guarantees the ELF object format.
     Testing __GNUC__ is necessary for the compound expression syntax.  */
# if defined __GLIBC__ && defined __ELF__ && defined __GNUC__
#  define GL_LINK_WARNING(message) \
     GL_LINK_WARNING1 (__FILE__, __LINE__, message)
#  define GL_LINK_WARNING1(file, line, message) \
     GL_LINK_WARNING2 (file, line, message)  /* macroexpand file and line */
#  define GL_LINK_WARNING2(file, line, message) \
     GL_LINK_WARNING3 (file ":" #line ": warning: " message)
#  define GL_LINK_WARNING3(message) \
     ({ static const char warning[sizeof (message)]		\
          __attribute__ ((__unused__,				\
                          __section__ (".gnu.warning"),		\
                          __aligned__ (1)))			\
          = message "\n";					\
        (void)0;						\
     })
# else
#  define GL_LINK_WARNING(message) ((void) 0)
# endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

/* Declare overridden functions.  */

#if 0
# define closedir rpl_closedir
extern int closedir (DIR *);
#endif

#if 1
# if !1 && !defined dirfd
/* Return the file descriptor associated with the given directory stream,
   or -1 if none exists.  */
extern int dirfd (DIR const *dir);
# endif
#elif defined GNULIB_POSIXCHECK
# undef dirfd
# define dirfd(d) \
    (GL_LINK_WARNING ("dirfd is unportable - " \
                      "use gnulib module dirfd for portability"), \
     dirfd (d))
#endif

#if 1
# if 1
#  undef fdopendir
#  define fdopendir rpl_fdopendir
# endif
# if !1 || 1
/* Open a directory stream visiting the given directory file
   descriptor.  Return NULL and set errno if fd is not visiting a
   directory.  On success, this function consumes fd (it will be
   implicitly closed either by this function or by a subsequent
   closedir).  */
extern DIR *fdopendir (int fd);
# endif
#elif defined GNULIB_POSIXCHECK
# undef fdopendir
# define fdopendir(f) \
    (GL_LINK_WARNING ("fdopendir is unportable - " \
                      "use gnulib module fdopendir for portability"), \
     fdopendir (f))
#endif

#if 0
# define opendir rpl_opendir
extern DIR * opendir (const char *);
#endif

#if 0
/* Scan the directory DIR, calling FILTER on each directory entry.
   Entries for which FILTER returns nonzero are individually malloc'd,
   sorted using qsort with CMP, and collected in a malloc'd array in
   *NAMELIST.  Returns the number of entries selected, or -1 on error.  */
# if !1
extern int scandir (const char *dir, struct dirent ***namelist,
		    int (*filter) (const struct dirent *),
		    int (*cmp) (const struct dirent **, const struct dirent **));
# endif
#elif defined GNULIB_POSIXCHECK
# undef scandir
# define scandir(d,n,f,c) \
    (GL_LINK_WARNING ("scandir is unportable - " \
                      "use gnulib module scandir for portability"), \
     scandir (d, n, f, c))
#endif

#if 0
/* Compare two 'struct dirent' entries alphabetically.  */
# if !1
extern int alphasort (const struct dirent **, const struct dirent **);
# endif
#elif defined GNULIB_POSIXCHECK
# undef alphasort
# define alphasort(a,b) \
    (GL_LINK_WARNING ("alphasort is unportable - " \
                      "use gnulib module alphasort for portability"), \
     alphasort (a, b))
#endif

#ifdef __cplusplus
}
#endif


#endif /* _GL_DIRENT_H */
#endif /* _GL_DIRENT_H */
