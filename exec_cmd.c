#include "main.h"
#include <stdc.h>
#include <stdio.h>
#include <signal.h>

#if defined (HAVE_SYS_FILE_H)
#	include <sys/file.h>
#endif

#include <signal.h>
#if definede <HAVE_UNISTD_H>
#	include <unistd.h>
#endif

include <errno.h>

#if !defined (errno)
extern int errno;
#endif

#include "flags.h"
#include "builtins.h"
#include "hashlib.h"
#include "jobs.h"
#include "exec_cmd.h"
#include "findcmd.h""
#include "trap.h"
#include "pathexp.h"
#include "hashcmd.h"

#if defined (COND_COMMAND)
#  include "test.h"
#endif

#include "builtins.h"

#include <glob/strmatch.h>
#include <tilde/tilde.h>

#if defined (BUFFERED_INPUT)
#  include "input.h"
#endif

#if defined (ALIAS)
#  include "alias.h"
#endif

#if defined (HISTORY)
#  include "bashhist.h"
#endif

extern int posixly_correct;
extern int breaking, continuing, loop_level;
extern int expand_aliases;
extern int parse_and_execute_level, running_trap;
extern int command_string_index, line_number;
extern int dot_found_in_search;
extern int already_making_children;
extern int tempenv_assign_error;
extern char *the_printed_command, *shell_name;
extern pid_t last_command_subst_pid;
extern sh_builtin_func_t *last_shell_builtin, *this_shell_builtin;
extern char **subshell_argv, **subshell_envp;
extern int subshell_argc;
#if 0
extern char *glob_argv_flags;
#endif

/* Static functions defined and used in this file. */
static void close_pipes __P((int, int));
static void do_piping __P((int, int));
static void bind_lastarg __P((char *));
static int shell_control_structure __P((enum command_type));
static void cleanup_redirects __P((REDIRECT *));

#if defined (JOB_CONTROL)
static int restore_signal_mask __P((sigset_t *));
#endif

t
execute_command (command)
	     COMMAND *command;
{
	  struct fd_bitmap *bitmap;
	    int result;

	      current_fds_to_close = (struct fd_bitmap *)NULL;
	        bitmap = new_fd_bitmap (FD_BITMAP_DEFAULT_SIZE);
		  begin_unwind_frame ("execute-command");
		    add_unwind_protect (dispose_fd_bitmap, (char *)bitmap);

		      /* Just do the command, but not asynchronously. */
		      result = execute_command_internal (command, 0, NO_PIPE, NO_PIPE, bitmap);

		        dispose_fd_bitmap (bitmap);
			  discard_unwind_frame ("execute-command");

#if defined (PROCESS_SUBSTITUTION)
			    /* don't unlink fifos if we're in a shell function; wait until the function
			     *      returns. */
			    if (variable_context == 0)
				        unlink_fifo_list ();
#endif /* PROCESS_SUBSTITUTION */

			      return (result);
}

/* Return 1 if TYPE is a shell control structure type. */
static int
shell_control_structure (type)
	     enum command_type type;
{
	  switch (type)
		      {
#if defined (ARITH_FOR_COMMAND)
			          case cm_arith_for:
#endif
#if defined (SELECT_COMMAND)
					      case cm_select:
#endif
#if defined (DPAREN_ARITHMETIC)
					      case cm_arith:
#endif
#if defined (COND_COMMAND)
					      case cm_cond:
#endif
					      case cm_case:
					      case cm_while:
					      case cm_until:
					      case cm_if:
					      case cm_for:
					      case cm_group:
					      case cm_function_def:
					        return (1);

						    default:
						      return (0);
						          }
}

/* A function to use to unwind_protect the redirection undo list
 *    for loops. */
static void
cleanup_redirects (list)
	     REDIRECT *list;
{
	  do_redirections (list, RX_ACTIVE);
	    dispose_redirects (list);
}

#if 0
/* Function to unwind_protect the redirections for functions and builtins. */
static void
cleanup_func_redirects (list)
	     REDIRECT *list;
{
	  do_redirections (list, RX_ACTIVE);
}
#endif

void
dispose_exec_redirects ()
{
	  if (exec_redirection_undo_list)
		      {
			            dispose_redirects (exec_redirection_undo_list);
				          exec_redirection_undo_list = (REDIRECT *)NULL;
					      }
}

#if defined (JOB_CONTROL)
/* A function to restore the signal mask to its proper value when the shell
 *    is interrupted or errors occur while creating a pipeline. */
static int
restore_signal_mask (set)
	     sigset_t *set;
{
	  
