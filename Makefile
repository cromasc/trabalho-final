file=main

run: 
	@gcc $(file).c -o $(file)
	@./$(file)
	@rm -r $(file)