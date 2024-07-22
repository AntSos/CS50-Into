import re


def main():
    # User input text
    text = input("Text: ")
    
    # Count letters in text
    letters_count = len(re.sub(r"[\s\.,!¡¿\?]", "", text))
    
    # Count words
    words_count = len(re.sub(r"[.,\/#!$%\^&\*;:{}=\-_`~¡¿?]", "", text).split())
    
    # Count sentences
    sentences_count = len(re.findall(r"[.!?]", text))
    
    # Calculation
    l = (letters_count / words_count) * 100
    
    s = (sentences_count / words_count) * 100

    index = 0.0588 * l - 0.296 * s - 15.8

    # Conditions 
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")
    

if __name__ == "__main__":
    main()