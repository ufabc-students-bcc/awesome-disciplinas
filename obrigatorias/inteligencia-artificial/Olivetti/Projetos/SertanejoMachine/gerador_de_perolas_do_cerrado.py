# -*- coding:utf-8 -*-

# Desabilita os avisos (para suprimir as mensagens do Keras)
def warn(*args, **kwargs):
        pass
import warnings
warnings.warn = warn

import joblib
import numpy as np
from keras.preprocessing.sequence import pad_sequences

class SertanejoBot():
    def __init__(self):
        self.model = joblib.load('./model/sertanejoBot.bin')
        self.tokenizer = joblib.load('./model/tokenizer.bin')
        self.max_length = joblib.load('./model/max_length.bin') - 1

        self.generated = ""
        self.seed = ""
        self.n_words = 4

    def user_input(self):
        user_input = input(">> Escreva um trecho da sua inspiração:\n")
        self.seed = user_input
        self.generated += self.seed

    def set_n_words(self):
        while True:
            n_words = int(input(">> Agora me diz quantas palavras você gostaria de gerar: "))
            if n_words < len(self.seed.split()) + 3 * self.max_length:
                self.n_words = n_words
                break
            else:
                print("Ihh rapaz...Eu ainda não sou tão bom, preciso de uma quantidade menor para a frase...")

    def generate(self):
        print("\n>> SEGURA PEÃO!!! O Sertanejo bot está inspirado ...\n")
        for _ in range(self.n_words):
            encoded = self.__encode(self.generated)
            proba = self.__get_proba(encoded)
            pred_word = ''
            for w, i in self.tokenizer.word_index.items():
                if i == proba:
                    pred_word = w
                    break
            self.generated += ' ' + pred_word

    def __encode(self, text):
        encoded = self.tokenizer.texts_to_sequences([text])[0]
        return pad_sequences([encoded], maxlen=self.max_length, padding='pre')

    def __get_proba(self, encoded):
        return self.model.predict_classes(encoded, verbose=0)

    def print_lyrics(self):
        print(">> Pronto! Segura esse meteoro da paixão:\n")
        print(self.generated)

    def reset(self):
        self.generated = ""
        self.seed = ""

if __name__ == "__main__":

    print("""
---
# Olá! Sou o SertanejoBot e vou te inspirar. Funciono da seguinte maneira:
# 1. Vou te pedir uma frase para inspiração. Quanto maior, melhor!
# 2. Você precisa me dizer quantas palavras quer após a sua frase.
# 3. Aguarde a magia acontecer...
---\n
Estou iniciando. Aguarde uns instantes...\n
          """)

    sbot = SertanejoBot()

    while True:
        sbot.user_input()
        sbot.set_n_words()
        sbot.generate()
        sbot.print_lyrics()

        print("\n---")
        option = input(">> Quer gerar mais uma letra? [S/n]")
        if option.lower() == 'n':
            print("\n>> Êta sofrência! Volta para mim algum dia...\n")
            break
        else:
            print('\n')
            sbot.reset()
