# CodeLab II – Coding Challenges

**Student:** Maria Fernanda Aragundi Ramos  
**Language:** C++

## Challenges

1. **CO2 Calculator:** Estimates journey emissions using distance
   in miles and the fuel type: diesel or petrol.
2. **Alexa Joke Teller:** Reads jokes from `randomJokes.txt`,
   selects one randomly and waits for Enter before revealing
   the punchline. Type `Alexa, tell me a joke` or `quit`.
3. **Book Manager:** Reads `bookData.txt` and allows users to
   view, borrow and return books using a menu.

The joke and book datasets were supplied on Ultra.

## How to Run

A C++17 compiler is required. Compile each challenge separately.

Open a terminal inside the challenge folder and run:

```bash
clang++ -std=c++17 main.cpp -o main
./main
```

For Challenges 2 and 3, keep the data file in the same folder
and run the program from that folder.

## Notes

- Enter fuel types in lowercase.
- Enter the Alexa request exactly, without extra spaces.
- Book IDs include leading zeros, for example `008`.
- Book borrowing changes last only during the current session.

## AI Acknowledgement

I acknowledge the use of ChatGPT (https://chatgpt.com/) to assist
with understanding programming concepts, developing and debugging
parts of the code, and reviewing the solutions against the challenge
requirements. I tested the programs on my Mac. ChatGPT also assisted
with translating and editing my descriptions and preparing this README.

## Reference

OpenAI (2026) ChatGPT [Generative AI tool].
Available at: https://chatgpt.com/ (Accessed: 27 October 2026).