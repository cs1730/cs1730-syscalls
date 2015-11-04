<!-- Creator     : groff version 1.18.1.4 -->
<!-- CreationDate: Tue Nov  3 20:06:03 2015 -->
<html>
<head>
<meta name="generator" content="groff -Thtml, see www.gnu.org">
<meta name="Content-Style" content="text/css">
<title>OPEN</title>
</head>
<body>

<h1 align=center>OPEN</h1>
<a href="#NAME">NAME</a><br>
<a href="#SYNOPSIS">SYNOPSIS</a><br>
<a href="#DESCRIPTION">DESCRIPTION</a><br>
<a href="#RETURN VALUE">RETURN VALUE</a><br>
<a href="#ERRORS">ERRORS</a><br>
<a href="#CONFORMING TO">CONFORMING TO</a><br>
<a href="#NOTES">NOTES</a><br>
<a href="#BUGS">BUGS</a><br>
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
<p>open, creat &minus; open and possibly create a file or
device</p>
</td>
</table>
<a name="SYNOPSIS"></a>
<h2>SYNOPSIS</h2>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<pre><b>#include &lt;sys/types.h&gt;
#include &lt;sys/stat.h&gt;
#include &lt;fcntl.h&gt;

int open(const char *</b><i>pathname</i><b>, int</b> <i>flags</i><b>);
int open(const char *</b><i>pathname</i><b>, int</b> <i>flags</i><b>, mode_t</b> <i>mode</i><b>);

int creat(const char *</b><i>pathname</i><b>, mode_t</b> <i>mode</i><b>);
</b></pre>
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
<p>Given a <i>pathname</i> for a file, <b>open</b>() returns
a file descriptor, a small, non-negative integer for use in
subsequent system calls (<b>read</b>(2), <b>write</b>(2),
<b>lseek</b>(2), <b>fcntl</b>(2), etc.). The file descriptor
returned by a successful call will be the lowest-numbered
file descriptor not currently open for the process.</p>
<!-- INDENTATION -->
<p>By default, the new file descriptor is set to remain open
across an <b>execve</b>(2) (i.e., the <b>FD_CLOEXEC</b> file
descriptor flag described in <b>fcntl</b>(2) is initially
disabled; the Linux-specific <b>O_CLOEXEC</b> flag,
described below, can be used to change this default). The
file offset is set to the beginning of the file (see
<b>lseek</b>(2)).</p>
<!-- INDENTATION -->
<p>A call to <b>open</b>() creates a new <i>open file
description</i>, an entry in the system-wide table of open
files. This entry records the file offset and the file
status flags (modifiable via the <b>fcntl</b>(2)
<b>F_SETFL</b> operation). A file descriptor is a reference
to one of these entries; this reference is unaffected if
<i>pathname</i> is subsequently removed or modified to refer
to a different file. The new open file description is
initially not shared with any other process, but sharing may
arise via <b>fork</b>(2).</p>
<!-- INDENTATION -->
<p>The argument <i>flags</i> must include one of the
following <i>access modes</i>: <b>O_RDONLY</b>,
<b>O_WRONLY</b>, or <b>O_RDWR</b>. These request opening the
file read-only, write-only, or read/write, respectively.</p>
<!-- INDENTATION -->
<p>In addition, zero or more file creation flags and file
status flags can be bitwise-<i>or</i>&rsquo;d in
<i>flags</i>. The <i>file creation flags</i> are
<b>O_CREAT</b>, <b>O_EXCL</b>, <b>O_NOCTTY</b>, and
<b>O_TRUNC</b>. The <i>file status flags</i> are all of the
remaining flags listed below. The distinction between these
two groups of flags is that the file status flags can be
retrieved and (in some cases) modified using
<b>fcntl</b>(2). The full list of file creation flags and
file status flags is as follows:</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>O_APPEND</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p>The file is opened in append mode. Before each
<b>write</b>(2), the file offset is positioned at the end of
the file, as if with <b>lseek</b>(2). <b>O_APPEND</b> may
lead to corrupted files on NFS file systems if more than one
process appends data to a file at once. This is because NFS
does not support appending to a file, so the client kernel
has to simulate it, which can&rsquo;t be done without a race
condition.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>O_ASYNC</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p>Enable signal-driven I/O: generate a signal (<b>SIGIO</b>
by default, but this can be changed via <b>fcntl</b>(2))
when input or output becomes possible on this file
descriptor. This feature is only available for terminals,
pseudo-terminals, sockets, and (since Linux 2.6) pipes and
FIFOs. See <b>fcntl</b>(2) for further details.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>O_CLOEXEC</b> (Since Linux 2.6.23)</p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p>Enable the close-on-exec flag for the new file
descriptor. Specifying this flag permits a program to avoid
additional <b>fcntl</b>(2) <b>F_SETFD</b> operations to set
the <b>FD_CLOEXEC</b> flag. Additionally, use of this flag
is essential in some multithreaded programs since using a
separate <b>fcntl</b>(2) <b>F_SETFD</b> operation to set the
<b>FD_CLOEXEC</b> flag does not suffice to avoid race
conditions where one thread opens a file descriptor at the
same time as another thread does a <b>fork</b>(2) plus
<b>execve</b>(2).</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>O_CREAT</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p>If the file does not exist it will be created. The owner
(user ID) of the file is set to the effective user ID of the
process. The group ownership (group ID) is set either to the
effective group ID of the process or to the group ID of the
parent directory (depending on file system type and mount
options, and the mode of the parent directory, see the mount
options <i>bsdgroups</i> and <i>sysvgroups</i> described in
<b>mount</b>(8)).</p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="20%"></td>
<td width="79%">
<p><i>mode</i> specifies the permissions to use in case a
new file is created. This argument must be supplied when
<b>O_CREAT</b> is specified in <i>flags</i>; if
<b>O_CREAT</b> is not specified, then <i>mode</i> is
ignored. The effective permissions are modified by the
process&rsquo;s <i>umask</i> in the usual way: The
permissions of the created file are <i>(mode &amp;
~umask)</i>. Note that this mode only applies to future
accesses of the newly created file; the <b>open</b>() call
that creates a read-only file may well return a read/write
file descriptor.</p>
<!-- INDENTATION -->
<p>The following symbolic constants are provided for
<i>mode</i>:</p>
</td>
</table>
<!-- TABS -->
<table width="100%" border=0 rules="none" frame="void"
       cols="4" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="11%">

<p><b>S_IRWXU</b></p>
</td>
<td width="1%"></td>
<td width="64%">

<p>00700 user (file owner) has read, write and execute
permission</p>
</td>
<tr valign="top" align="left">
<td width="21%"></td>
<td width="11%">

<p><b>S_IRUSR</b></p>
</td>
<td width="1%"></td>
<td width="64%">

<p>00400 user has read permission</p>
</td>
<tr valign="top" align="left">
<td width="21%"></td>
<td width="11%">

<p><b>S_IWUSR</b></p>
</td>
<td width="1%"></td>
<td width="64%">

<p>00200 user has write permission</p>
</td>
<tr valign="top" align="left">
<td width="21%"></td>
<td width="11%">

<p><b>S_IXUSR</b></p>
</td>
<td width="1%"></td>
<td width="64%">

<p>00100 user has execute permission</p>
</td>
<tr valign="top" align="left">
<td width="21%"></td>
<td width="11%">

<p><b>S_IRWXG</b></p>
</td>
<td width="1%"></td>
<td width="64%">

<p>00070 group has read, write and execute permission</p>
</td>
<tr valign="top" align="left">
<td width="21%"></td>
<td width="11%">

<p><b>S_IRGRP</b></p>
</td>
<td width="1%"></td>
<td width="64%">

<p>00040 group has read permission</p>
</td>
<tr valign="top" align="left">
<td width="21%"></td>
<td width="11%">

<p><b>S_IWGRP</b></p>
</td>
<td width="1%"></td>
<td width="64%">

<p>00020 group has write permission</p>
</td>
<tr valign="top" align="left">
<td width="21%"></td>
<td width="11%">

<p><b>S_IXGRP</b></p>
</td>
<td width="1%"></td>
<td width="64%">

<p>00010 group has execute permission</p>
</td>
<tr valign="top" align="left">
<td width="21%"></td>
<td width="11%">

<p><b>S_IRWXO</b></p>
</td>
<td width="1%"></td>
<td width="64%">

<p>00007 others have read, write and execute permission</p>
</td>
<tr valign="top" align="left">
<td width="21%"></td>
<td width="11%">

<p><b>S_IROTH</b></p>
</td>
<td width="1%"></td>
<td width="64%">

<p>00004 others have read permission</p>
</td>
<tr valign="top" align="left">
<td width="21%"></td>
<td width="11%">

<p><b>S_IWOTH</b></p>
</td>
<td width="1%"></td>
<td width="64%">

<p>00002 others have write permission</p>
</td>
<tr valign="top" align="left">
<td width="21%"></td>
<td width="11%">

<p><b>S_IXOTH</b></p>
</td>
<td width="1%"></td>
<td width="64%">

<p>00001 others have execute permission</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>O_DIRECT</b> (Since Linux 2.4.10)</p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p>Try to minimize cache effects of the I/O to and from this
file. In general this will degrade performance, but it is
useful in special situations, such as when applications do
their own caching. File I/O is done directly to/from user
space buffers. The I/O is synchronous, that is, at the
completion of a <b>read</b>(2) or <b>write</b>(2), data is
guaranteed to have been transferred. See <b>NOTES</b> below
for further discussion.</p>
<!-- INDENTATION -->
<p>A semantically similar (but deprecated) interface for
block devices is described in <b>raw</b>(8).</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>O_DIRECTORY</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p>If <i>pathname</i> is not a directory, cause the open to
fail. This flag is Linux-specific, and was added in kernel
version 2.1.126, to avoid denial-of-service problems if
<b>opendir</b>(3) is called on a FIFO or tape device, but
should not be used outside of the implementation of
<b>opendir</b>(3).</p>
</td>
</table>
<!-- TABS -->
<table width="100%" border=0 rules="none" frame="void"
       cols="4" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="8%">

<p><b>O_EXCL</b></p>
</td>
<td width="1%"></td>
<td width="77%">

<p>Ensure that this call creates the file: if this flag is
specified in conjunction with <b>O_CREAT</b>, and
<i>pathname</i> already exists, then <b>open</b>() will
fail. The behavior of <b>O_EXCL</b> is undefined if
<b>O_CREAT</b> is not specified.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p>When these two flags are specified, symbolic links are
not followed: if <i>pathname</i> is a symbolic link, then
<b>open</b>() fails regardless of where the symbolic link
points to.</p>
<!-- INDENTATION -->
<p><b>O_EXCL</b> is only supported on NFS when using NFSv3
or later on kernel 2.6 or later. In environments where NFS
<b>O_EXCL</b> support is not provided, programs that rely on
it for performing locking tasks will contain a race
condition. Portable programs that want to perform atomic
file locking using a lockfile, and need to avoid reliance on
NFS support for <b>O_EXCL</b>, can create a unique file on
the same file system (e.g., incorporating hostname and PID),
and use <b>link</b>(2) to make a link to the lockfile. If
<b>link</b>(2) returns 0, the lock is successful. Otherwise,
use <b>stat</b>(2) on the unique file to check if its link
count has increased to 2, in which case the lock is also
successful.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>O_LARGEFILE</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p>(LFS) Allow files whose sizes cannot be represented in an
<i>off_t</i> (but can be represented in an <i>off64_t</i>)
to be opened. The <b>_LARGEFILE64_SOURCE</b> macro must be
defined in order to obtain this definition. Setting the
<b>_FILE_OFFSET_BITS</b> feature test macro to 64 (rather
than using <b>O_LARGEFILE</b>) is the preferred method of
obtaining method of accessing large files on 32-bit systems
(see <b>feature_test_macros</b>(7)).</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>O_NOATIME</b> (Since Linux 2.6.8)</p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p>Do not update the file last access time (st_atime in the
inode) when the file is <b>read</b>(2). This flag is
intended for use by indexing or backup programs, where its
use can significantly reduce the amount of disk activity.
This flag may not be effective on all file systems. One
example is NFS, where the server maintains the access
time.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>O_NOCTTY</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p>If <i>pathname</i> refers to a terminal device &mdash;
see <b>tty</b>(4) &mdash; it will not become the
process&rsquo;s controlling terminal even if the process
does not have one.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>O_NOFOLLOW</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p>If <i>pathname</i> is a symbolic link, then the open
fails. This is a FreeBSD extension, which was added to Linux
in version 2.1.126. Symbolic links in earlier components of
the pathname will still be followed.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>O_NONBLOCK</b> or <b>O_NDELAY</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p>When possible, the file is opened in non-blocking mode.
Neither the <b>open</b>() nor any subsequent operations on
the file descriptor which is returned will cause the calling
process to wait. For the handling of FIFOs (named pipes),
see also <b>fifo</b>(7). For a discussion of the effect of
<b>O_NONBLOCK</b> in conjunction with mandatory file locks
and with file leases, see <b>fcntl</b>(2).</p>
</td>
</table>
<!-- TABS -->
<table width="100%" border=0 rules="none" frame="void"
       cols="4" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="8%">

<p><b>O_SYNC</b></p>
</td>
<td width="1%"></td>
<td width="77%">

<p>The file is opened for synchronous I/O. Any
<b>write</b>(2)s on the resulting file descriptor will block
the calling process until the data has been physically
written to the underlying hardware. <i>But see NOTES
below</i>.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>O_TRUNC</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p>If the file already exists and is a regular file and the
open mode allows writing (i.e., is <b>O_RDWR</b> or
<b>O_WRONLY</b>) it will be truncated to length 0. If the
file is a FIFO or terminal device file, the <b>O_TRUNC</b>
flag is ignored. Otherwise the effect of <b>O_TRUNC</b> is
unspecified.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p>Some of these optional flags can be altered using
<b>fcntl</b>(2) after the file has been opened.</p>
<!-- INDENTATION -->
<p><b>creat</b>() is equivalent to <b>open</b>() with
<i>flags</i> equal to <b>O_CREAT|O_WRONLY|O_TRUNC</b>.</p>
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
<p><b>open</b>() and <b>creat</b>() return the new file
descriptor, or &minus;1 if an error occurred (in which case,
<i>errno</i> is set appropriately).</p>
</td>
</table>
<a name="ERRORS"></a>
<h2>ERRORS</h2>
<!-- TABS -->
<table width="100%" border=0 rules="none" frame="void"
       cols="3" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="10%">

<p><b>EACCES</b></p>
</td>
<td width="77%">

<p>The requested access to the file is not allowed, or
search permission is denied for one of the directories in
the path prefix of <i>pathname</i>, or the file did not
exist yet and write access to the parent directory is not
allowed. (See also <b>path_resolution</b>(7).)</p>
</td>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="10%">

<p><b>EEXIST</b></p>
</td>
<td width="77%">

<p><i>pathname</i> already exists and <b>O_CREAT</b> and
<b>O_EXCL</b> were used.</p>
</td>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="10%">

<p><b>EFAULT</b></p>
</td>
<td width="77%">

<p><i>pathname</i> points outside your accessible address
space.</p>
</td>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="10%">

<p><b>EFBIG</b></p>
</td>
<td width="77%">

<p>See <b>EOVERFLOW</b>.</p>
</td>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="10%">

<p><b>EINTR</b></p>
</td>
<td width="77%">

<p>While blocked waiting to complete an open of a slow
device (e.g., a FIFO; see <b>fifo</b>(7)), the call was
interrupted by a signal handler; see <b>signal</b>(7).</p>
</td>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="10%">

<p><b>EISDIR</b></p>
</td>
<td width="77%">

<p><i>pathname</i> refers to a directory and the access
requested involved writing (that is, <b>O_WRONLY</b> or
<b>O_RDWR</b> is set).</p>
</td>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="10%">

<p><b>ELOOP</b></p>
</td>
<td width="77%">

<p>Too many symbolic links were encountered in resolving
<i>pathname</i>, or <b>O_NOFOLLOW</b> was specified but
<i>pathname</i> was a symbolic link.</p>
</td>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="10%">

<p><b>EMFILE</b></p>
</td>
<td width="77%">

<p>The process already has the maximum number of files
open.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>ENAMETOOLONG</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p><i>pathname</i> was too long.</p>
</td>
</table>
<!-- TABS -->
<table width="100%" border=0 rules="none" frame="void"
       cols="3" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="10%">

<p><b>ENFILE</b></p>
</td>
<td width="77%">

<p>The system limit on the total number of open files has
been reached.</p>
</td>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="10%">

<p><b>ENODEV</b></p>
</td>
<td width="77%">

<p><i>pathname</i> refers to a device special file and no
corresponding device exists. (This is a Linux kernel bug; in
this situation <b>ENXIO</b> must be returned.)</p>
</td>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="10%">

<p><b>ENOENT</b></p>
</td>
<td width="77%">

<p><b>O_CREAT</b> is not set and the named file does not
exist. Or, a directory component in <i>pathname</i> does not
exist or is a dangling symbolic link.</p>
</td>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="10%">

<p><b>ENOMEM</b></p>
</td>
<td width="77%">

<p>Insufficient kernel memory was available.</p>
</td>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="10%">

<p><b>ENOSPC</b></p>
</td>
<td width="77%">

<p><i>pathname</i> was to be created but the device
containing <i>pathname</i> has no room for the new file.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>ENOTDIR</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p>A component used as a directory in <i>pathname</i> is
not, in fact, a directory, or <b>O_DIRECTORY</b> was
specified and <i>pathname</i> was not a directory.</p>
</td>
</table>
<!-- TABS -->
<table width="100%" border=0 rules="none" frame="void"
       cols="4" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="7%">

<p><b>ENXIO</b></p>
</td>
<td width="2%"></td>
<td width="77%">

<p><b>O_NONBLOCK</b> | <b>O_WRONLY</b> is set, the named
file is a FIFO and no process has the file open for reading.
Or, the file is a device special file and no corresponding
device exists.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>EOVERFLOW</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p><i>pathname</i> refers to a regular file that is too
large to be opened. The usual scenario here is that an
application compiled on a 32-bit platform without
<i>-D_FILE_OFFSET_BITS=64</i> tried to open a file whose
size exceeds <i>(2&lt;&lt;31)-1</i> bits; see also
<b>O_LARGEFILE</b> above. This is the error specified by
POSIX.1-2001; in kernels before 2.6.24, Linux gave the error
<b>EFBIG</b> for this case.</p>
</td>
</table>
<!-- TABS -->
<table width="100%" border=0 rules="none" frame="void"
       cols="4" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="7%">

<p><b>EPERM</b></p>
</td>
<td width="2%"></td>
<td width="77%">

<p>The <b>O_NOATIME</b> flag was specified, but the
effective user ID of the caller did not match the owner of
the file and the caller was not privileged
(<b>CAP_FOWNER</b>).</p>
</td>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="7%">

<p><b>EROFS</b></p>
</td>
<td width="2%"></td>
<td width="77%">

<p><i>pathname</i> refers to a file on a read-only file
system and write access was requested.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>ETXTBSY</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p><i>pathname</i> refers to an executable image which is
currently being executed and write access was requested.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p><b>EWOULDBLOCK</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="21%"></td>
<td width="77%">
<p>The <b>O_NONBLOCK</b> flag was specified, and an
incompatible lease was held on the file (see
<b>fcntl</b>(2)).</p>
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
<p>SVr4, 4.3BSD, POSIX.1-2001. The <b>O_DIRECTORY</b>,
<b>O_NOATIME</b>, and <b>O_NOFOLLOW</b> flags are
Linux-specific, and one may need to define
<b>_GNU_SOURCE</b> to obtain their definitions.</p>
<!-- INDENTATION -->
<p>The <b>O_CLOEXEC</b> flag is not specified in
POSIX.1-2001, but is specified in POSIX.1-2008.</p>
<!-- INDENTATION -->
<p><b>O_DIRECT</b> is not specified in POSIX; one has to
define <b>_GNU_SOURCE</b> to get its definition.</p>
</td>
</table>
<a name="NOTES"></a>
<h2>NOTES</h2>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p>Under Linux, the <b>O_NONBLOCK</b> flag indicates that
one wants to open but does not necessarily have the
intention to read or write. This is typically used to open
devices in order to get a file descriptor for use with
<b>ioctl</b>(2).</p>
<!-- INDENTATION -->
<p>Unlike the other values that can be specified in
<i>flags</i>, the <i>access mode</i> values <b>O_RDONLY</b>,
<b>O_WRONLY</b>, and <b>O_RDWR</b>, do not specify
individual bits. Rather, they define the low order two bits
of <i>flags</i>, and are defined respectively as 0, 1, and
2. In other words, the combination <b>O_RDONLY |
O_WRONLY</b> is a logical error, and certainly does not have
the same meaning as <b>O_RDWR</b>. Linux reserves the
special, non-standard access mode 3 (binary 11) in
<i>flags</i> to mean: check for read and write permission on
the file and return a descriptor that can&rsquo;t be used
for reading or writing. This non-standard access mode is
used by some Linux drivers to return a descriptor that is
only to be used for device-specific <b>ioctl</b>(2)
operations.</p>
<!-- INDENTATION -->
<p>The (undefined) effect of <b>O_RDONLY | O_TRUNC</b>
varies among implementations. On many systems the file is
actually truncated.</p>
<!-- INDENTATION -->
<p>There are many infelicities in the protocol underlying
NFS, affecting amongst others <b>O_SYNC</b> and
<b>O_NDELAY</b>.</p>
<!-- INDENTATION -->
<p>POSIX provides for three different variants of
synchronized I/O, corresponding to the flags <b>O_SYNC</b>,
<b>O_DSYNC</b> and <b>O_RSYNC</b>. Currently (2.1.130) these
are all synonymous under Linux.</p>
<!-- INDENTATION -->
<p>Note that <b>open</b>() can open device special files,
but <b>creat</b>() cannot create them; use <b>mknod</b>(2)
instead.</p>
<!-- INDENTATION -->
<p>On NFS file systems with UID mapping enabled,
<b>open</b>() may return a file descriptor but, for example,
<b>read</b>(2) requests are denied with <b>EACCES</b>. This
is because the client performs <b>open</b>() by checking the
permissions, but UID mapping is performed by the server upon
read and write requests.</p>
<!-- INDENTATION -->
<p>If the file is newly created, its <i>st_atime</i>,
<i>st_ctime</i>, <i>st_mtime</i> fields (respectively, time
of last access, time of last status change, and time of last
modification; see <b>stat</b>(2)) are set to the current
time, and so are the <i>st_ctime</i> and <i>st_mtime</i>
fields of the parent directory. Otherwise, if the file is
modified because of the <b>O_TRUNC</b> flag, its st_ctime
and st_mtime fields are set to the current time.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="4%"></td>
<td width="95%">
<p><b>O_DIRECT</b></p></td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p>The <b>O_DIRECT</b> flag may impose alignment
restrictions on the length and address of userspace buffers
and the file offset of I/Os. In Linux alignment restrictions
vary by file system and kernel version and might be absent
entirely. However there is currently no file
system&minus;independent interface for an application to
discover these restrictions for a given file or file system.
Some file systems provide their own interfaces for doing so,
for example the <b>XFS_IOC_DIOINFO</b> operation in
<b>xfsctl</b>(3).</p>
<!-- INDENTATION -->
<p>Under Linux 2.4, transfer sizes, and the alignment of the
user buffer and the file offset must all be multiples of the
logical block size of the file system. Under Linux 2.6,
alignment to 512-byte boundaries suffices.</p>
<!-- INDENTATION -->
<p>The <b>O_DIRECT</b> flag was introduced in SGI IRIX,
where it has alignment restrictions similar to those of
Linux 2.4. IRIX has also a <b>fcntl</b>(2) call to query
appropriate alignments, and sizes. FreeBSD 4.x introduced a
flag of the same name, but without alignment
restrictions.</p>
<!-- INDENTATION -->
<p><b>O_DIRECT</b> support was added under Linux in kernel
version 2.4.10. Older Linux kernels simply ignore this flag.
Some file systems may not implement the flag and
<b>open</b>() will fail with <b>EINVAL</b> if it is
used.</p>
<!-- INDENTATION -->
<p>Applications should avoid mixing <b>O_DIRECT</b> and
normal I/O to the same file, and especially to overlapping
byte regions in the same file. Even when the file system
correctly handles the coherency issues in this situation,
overall I/O throughput is likely to be slower than using
either mode alone. Likewise, applications should avoid
mixing <b>mmap</b>(2) of files with direct I/O to the same
files.</p>
<!-- INDENTATION -->
<p>The behaviour of <b>O_DIRECT</b> with NFS will differ
from local file systems. Older kernels, or kernels
configured in certain ways, may not support this
combination. The NFS protocol does not support passing the
flag to the server, so <b>O_DIRECT</b> I/O will only bypass
the page cache on the client; the server may still cache the
I/O. The client asks the server to make the I/O synchronous
to preserve the synchronous semantics of <b>O_DIRECT</b>.
Some servers will perform poorly under these circumstances,
especially if the I/O size is small. Some servers may also
be configured to lie to clients about the I/O having reached
stable storage; this will avoid the performance penalty at
some risk to data integrity in the event of server power
failure. The Linux NFS client places no alignment
restrictions on <b>O_DIRECT</b> I/O.</p>
<!-- INDENTATION -->
<p>In summary, <b>O_DIRECT</b> is a potentially powerful
tool that should be used with caution. It is recommended
that applications treat use of <b>O_DIRECT</b> as a
performance option which is disabled by default.</p>
</td>
</table>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="20%"></td>
<td width="79%">
<p>&quot;The thing that has always disturbed me about
O_DIRECT is that the whole interface is just stupid, and was
probably designed by a deranged monkey on some serious
mind-controlling substances.&quot; &mdash; Linus</p></td>
</table>
<a name="BUGS"></a>
<h2>BUGS</h2>
<!-- INDENTATION -->
<table width="100%" border=0 rules="none" frame="void"
       cols="2" cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="10%"></td>
<td width="89%">
<p>Currently, it is not possible to enable signal-driven I/O
by specifying <b>O_ASYNC</b> when calling <b>open</b>(); use
<b>fcntl</b>(2) to enable this flag.</p>
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
<p><b>chmod</b>(2), <b>chown</b>(2), <b>close</b>(2),
<b>dup</b>(2), <b>fcntl</b>(2), <b>link</b>(2),
<b>lseek</b>(2), <b>mknod</b>(2), <b>mmap</b>(2),
<b>mount</b>(2), <b>openat</b>(2), <b>read</b>(2),
<b>socket</b>(2), <b>stat</b>(2), <b>umask</b>(2),
<b>unlink</b>(2), <b>write</b>(2), <b>fopen</b>(3),
<b>feature_test_macros</b>(7), <b>fifo</b>(7),
<b>path_resolution</b>(7), <b>symlink</b>(7)</p>
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
