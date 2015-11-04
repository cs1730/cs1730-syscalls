<!-- Creator     : groff version 1.18.1.4 -->
<!-- CreationDate: Tue Nov  3 19:50:35 2015 -->
<html>
<head>
<meta name="generator" content="groff -Thtml, see www.gnu.org">
<meta name="Content-Style" content="text/css">
<title>INTRO</title>
</head>
<body>

<h1 align=center>INTRO</h1>
<a href="#NAME">NAME</a><br>
<a href="#DESCRIPTION">DESCRIPTION</a><br>
<a href="#RETURN VALUE">RETURN VALUE</a><br>
<a href="#CONFORMING TO">CONFORMING TO</a><br>
<a href="#NOTES">NOTES</a><br>
<a href="#SEE ALSO">SEE ALSO</a><br>
<a href="#COLOPHON">COLOPHON</a><br>

<hr>
<a name="NAME"></a>
<h2>NAME</h2>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p>intro &minus; Introduction to system calls</p>
</td>
</table>
<a name="DESCRIPTION"></a>
<h2>DESCRIPTION</h2>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p>Section 2 of the manual describes the Linux system calls.
A system call is an entry point into the Linux kernel.
Usually, system calls are not invoked directly: instead,
most system calls have corresponding C library wrapper
functions which perform the steps required (e.g., trapping
to kernel mode) in order to invoke the system call. Thus,
making a system call looks the same as invoking a normal
library function.</p>
<!-- INDENTATION -->
<p>For a list of the Linux system calls, see
<b>syscalls</b>(2).</p>
</td>
</table>
<a name="RETURN VALUE"></a>
<h2>RETURN VALUE</h2>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p>On error, most system calls return a negative error
number (i.e., the negated value of one of the constants
described in <b>errno</b>(3)). The C library wrapper hides
this detail from the caller: when a system call returns a
negative value, the wrapper copies the absolute value into
the <i>errno</i> variable, and returns &minus;1 as the
return value of the wrapper.</p>
<!-- INDENTATION -->
<p>The value returned by a successful system call depends on
the call. Many system calls return 0 on success, but some
can return non-zero values from a successful call. The
details are described in the individual manual pages.</p>
<!-- INDENTATION -->
<p>In some cases, the programmer must define a feature test
macro in order to obtain the declaration of a system call
from the header file specified in the man page SYNOPSIS
section. In such cases, the required macro is described in
the man page. For further information on feature test
macros, see <b>feature_test_macros</b>(7).</p>
</td>
</table>
<a name="CONFORMING TO"></a>
<h2>CONFORMING TO</h2>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p>Certain terms and abbreviations are used to indicate Unix
variants and standards to which calls in this section
conform. See <b>standards</b>(7).</p>
</td>
</table>
<a name="NOTES"></a>
<h2>NOTES</h2>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="4%"></td>
<td width="95%">
<p><b>Calling Directly</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p>In most cases, it is unnecessary to invoke a system call
directly, but there are times when the Standard C library
does not implement a nice wrapper function for you. In this
case, the programmer must manually invoke the system call
using <b>syscall</b>(2). Historically, this was also
possible using one of the _syscall macros described in
<b>_syscall</b>(2).</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="4%"></td>
<td width="95%">
<p><b>Authors and Copyright Terms</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p>Look at the header of the manual page source for the
author(s) and copyright conditions. Note that these can be
different from page to page!</p>
</td>
</table>
<a name="SEE ALSO"></a>
<h2>SEE ALSO</h2>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>_syscall</b>(2), <b>syscall</b>(2), <b>errno</b>(3),
<b>feature_test_macros</b>(7), <b>standards</b>(7)</p>
</td>
</table>
<a name="COLOPHON"></a>
<h2>COLOPHON</h2>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p>This page is part of release 3.22 of the Linux
<i>man-pages</i> project. A description of the project, and
information about reporting bugs, can be found at
http://www.kernel.org/doc/man-pages/.</p>
</td>
</table>
<hr>
</body>
</html>
