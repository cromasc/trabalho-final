file=ufu_cli

run: 
	@gcc $(file).c -o $(file).out
	@./$(file).out
	@rm -r $(file).out