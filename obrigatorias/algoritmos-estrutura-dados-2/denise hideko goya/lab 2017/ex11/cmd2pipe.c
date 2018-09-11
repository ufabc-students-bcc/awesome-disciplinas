#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char *argv[])
{
	//cria um monte de variavel
	char ch;
	FILE *stream;
	int mypipe = 0;
	char cmd[128];
	
	//verifica se a pessoa não chamou errado
	if (argc <3)
	{
		fprintf (stderr, "Usage: %s <pipe_name> <command [arguments]>\n", argv[0]);
		return -1;
	}

	//avisa se der erro ao criar o pipe
	if (mkfifo (argv[1], 0777) < 0 && errno != EEXIST)
	{
		fprintf (stderr, "Erro ao tentar criar o pipe (error %i: %s)\n", errno, strerror (errno));
		return -1;
	}

	//avisa se tem erro ao abrir o pipe
	if ((mypipe = open (argv[1], O_WRONLY)) < 0)
	{
		fprintf (stderr, "Erro ao tentar abrir o pipe (error %i: %s)\n", errno, strerror (errno));
		return -1;
	}

	// copies up to n characters from the string pointed to, by src to dest
	// copia do arg 2 pro cmd
	strncpy (cmd, argv[2], sizeof (cmd));
	int i;
	
	// escreve parâmetro no buffer?
	for (i = 3; i < argc; ++i)
	{
		snprintf (cmd, sizeof (cmd), "%s %s", cmd, argv[i]);
	}

	//avisa se der erro ao abrir o comando
	if ((stream = popen (cmd, "r")) == NULL)
	{
		fprintf (stderr, "Erro ao tentar abrir o comando %s.\n", argv[2]);
		return -1;
	}
	
	// escreve o pipe?
	while (fread (&ch, sizeof (char), 1, stream))
	{
		write (mypipe, &ch, sizeof (ch));
	}
	
	printf ("Exit code: %i :o\n", pclose (stream));

	close (mypipe);
	unlink (argv[1]);
}
