module Main where

-- cria uma lista de 5 números ao quadrado
xs = [x^2 | x <- [1..5]]

-- função que traz os dividores de n
divisores::Int -> [Int]
divisores n = [x | x <- [1..n], n `mod` x==0]

-- função que verifica se um numero n é primo
primo :: Int -> Bool
primo n = divisores n == [1, n]

-- verifica os primeiros n numeros primos
primos :: Int -> [Int]
primos n = [x | x <- [1..n], primo x]

-- retorna todos os primos do mundo
todosPrimos :: [Int]
todosPrimos = 
  2:3: [n | k <- [1..], -- a lista sempre vai começar com 2, 3 e continuar a partir dai
            n <- [6 * k - 1, 6 * k + 1],
            primo n]
            
{-
Cria uma lista de fibonacci com a função zipWith, que junta duas listas de acordo com
um parâmetro dado, que no caso é a soma, então ele vai somar as duas listas
Os parametros pro zipwith é o proprio fibonacci normal com um fibonacci que inicia com 
zero antes, ou seja, junta n com n + 1
-}
fibs :: [Integer]
fibs = 1:(zipWith (+) fibs (0:fibs))

{-
quick sort
concatena menores numeros com os maiores 
usa 2 funções que são definidas na hora dentro da função
-}
qsort::Ord a => [a] -> [a]
qsort[] = []
qsort (x:xs) = qsort menores ++ [x] ++ qsort maiores -- vai concatenando na lista menores na frente e maiores atras
  where
    menores = [a | a <- xs, a <= x]
    maiores = [b | b <- xs, b > x]
    
{-
Exercício: Dadas as funções dobra e somaUm aplique-as em sequência na lista [1..10] utilizando map:
-}
dobra :: Num a => a -> a 
dobra x = 2 * x 

somaUm :: Num a => a -> a 
somaUm x = x + 1

ex1:: [Num] -> Num
ex1 ns = map (somaUm . dobra) ns -- o ponto é a composição de funções f(g(x))


main :: IO () -- indica que é o módulo principal
main = do -- início da função principal
  print(1)