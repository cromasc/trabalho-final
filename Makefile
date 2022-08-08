run: 
	@gcc ufu_cli.c -o ufu_cli.out
	@./ufu_cli.out
	@rm -r ufu_cli.out
	@clear