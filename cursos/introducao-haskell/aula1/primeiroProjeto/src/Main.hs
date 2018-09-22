module Main where

-- função que dobra o valor de x
dobra x = x + x

-- aplica a função dobra 2x para quadruplicar
quadruplica x = dobra (dobra x)

{- 
Função que aplica a função product (que multiplica valores)
em um grupo que números que vão de 1 a x
A notação é parecida com a da matemática
-}
fatorial x = product[1..x]

-- Hello world criado automaticamente
main :: IO () -- indica que é o módulo principal
main = do -- início da função principal
  putStrLn "hello world" -- imprime hello world
-- Fim da parte criada automaticamente


