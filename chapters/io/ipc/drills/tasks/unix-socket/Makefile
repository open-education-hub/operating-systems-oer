PYTHON = python3
SCRIPT = generate_skels.py

skels:
	mkdir -p support/
	$(PYTHON) $(SCRIPT) --input ./solution/src --output ./support/src
	mkdir -p support/tests
	cp solution/tests/checker.sh support/tests/checker.sh

clean:
	rm -rf support/
