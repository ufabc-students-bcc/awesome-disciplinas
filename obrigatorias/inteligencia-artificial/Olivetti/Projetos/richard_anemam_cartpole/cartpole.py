'''
Nome: Richard Anemam da Costa
RA: 11049114
Descrição: aprendizado por reforço no problema do CartPole-v1
'''

import gym
import numpy as np

env = gym.make('CartPole-v1')

NUM_EPISODES = 10000
BEST_POLICY = 100

def play(weight):
    observation = env.reset()

    done = False
    score = 0
    observations = []

    for _ in range(NUM_EPISODES):
        observations += [observation.tolist()]
        env.render()
        print(observation)

        if done:
          break

        outcome = policy(weight, observation)
        dsoftmax = softmax_grad(outcome)

        action = 1 if dsoftmax > 0 else 0

        observation, reward, done, info = env.step(action)
        score += reward

    return score, observations

def policy(weight, observation):
    z = np.dot(weight, observation)
    exp = np.exp(z)
    return exp

def softmax_grad(softmax):
    s = softmax.reshape(-1,1)
    return np.diagflat(s) - np.dot(s, s.T)

def main():
    max = (0, [], [])
    for _ in range(BEST_POLICY):
        weight = np.random.rand(1,4)-0.5
        score, observations = play(weight)

        if score > max[0]:
            max = (score, observations, weight)

    print('Max Score', max[0])

if __name__ == "__main__":
   main()
