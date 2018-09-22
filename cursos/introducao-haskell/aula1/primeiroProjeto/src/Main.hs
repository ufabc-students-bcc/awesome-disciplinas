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


{-
Exercício 1: criar uma função que calcule as raízes de uma função
de segundo grau
-}
raiz2Grau :: (Ord a, Floating a) => a -> a -> a -> (a,a)
raiz2Grau a b c  
  | delta  >= 0 = (x1, x2) -- esse | significa "tal que" igual na matemática mesmo
  | otherwise   = error "Raízes negativas" -- os | e os sinais de igual tem que estar alinhados
  where
    x1 = ((-b) + sqDelta)/ (2*a)
    x2 = ((-b) + sqDelta)/ (2*a)

    sqDelta = sqrt delta
    delta = b^2 - 4*a*c

{- 
Exercício 2: Pegar a seguinte função e diminuir o número de clausulas
(&&) :: Bool -> Bool -> Bool
True  && True  = True
True  && False = False
False && True  = False
False && False = False

Poderia ter usado
True && True = True
_ && _       = False
Isso porque o _ indica que tanto faz o conteúdo daquela posição
e também quando ele encontra a primeira condição, ele para
de rodar a função
-}
(&&&) :: Bool -> Bool -> Bool
(&&&) a b 
  | a == True && b == True = True
  | otherwise              = False

{-
Exercício 3:
O operador !! recupera o i-ésimo elemento da lista, com índice começando do 0
Implemente o operador !! utilizando as funções
-}
xs !!* n = head (drop n xs)

{-
Exercício 4: Implemente a função take.
Se n <= 0 deve retornar uma lista vazia
-}
toma :: Int -> [a] -> [a]
toma n _ | n <= 0 = [] -- se n <= retorna lista vazia
toma _ []         = [] -- se a lista for vazia retorna vazio, independentemente no n
toma _ (x:xs)     = x : take (n - 1) xs -- faz uma chamada recursiva para ir adicionando os números na lista

-- Hello world criado automaticamente
main :: IO () -- indica que é o módulo principal
main = do -- início da função principal
  putStrLn "hello world" -- imprime hello world
-- Fim da parte criada automaticamente


