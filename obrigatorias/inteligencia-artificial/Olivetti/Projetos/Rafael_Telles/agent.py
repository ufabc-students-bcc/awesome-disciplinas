import random
import time
from itertools import product

import numpy as np

import gym
from gym import logger

env = gym.make('MountainCarContinuous-v0')

POPULATION_SIZE = 10
MAX_POPULATION_SIZE = 100
MUTATION_CHANCE = 0.5
BREEDING_CHANCE = 0.5
CURRENT_AGENTS_COUNT = 0


#  Constants got from continuous_mountain_car.py
POSITION_GRANULARITY = 10
POSITION_MIN = -0.6
POSITION_MAX = 1.2

VELOCITY_GRANULARITY = 10
VELOCITY_MIN = -0.07
VELOCITY_MAX = 0.07


def normalize(x, min_x, max_x, granularity):
    if x == 0:
        return 0
    return 1 + min(int((max(x - min_x, 0) / (max_x - min_x)) * (granularity - 2)), granularity - 2)


def position_range():
    return range(POSITION_GRANULARITY)


def normalize_position(position):
    return normalize(position, POSITION_MIN, POSITION_MAX, POSITION_GRANULARITY)


def velocity_range():
    return range(VELOCITY_GRANULARITY)


def normalize_velocity(velocity):
    return normalize(velocity, VELOCITY_MIN, VELOCITY_MAX, VELOCITY_GRANULARITY)


def random_power():
    return (np.random.rand() - 0.5) * 2


class MyAgent(object):
    def __init__(self, policy=None):
        self.env = env
        if policy is not None:
            self.policy = policy
        else:
            self.policy = {k: random_power() for k in product(position_range(), velocity_range())}

        global CURRENT_AGENTS_COUNT
        self._id = CURRENT_AGENTS_COUNT
        CURRENT_AGENTS_COUNT += 1

    def __repr__(self):
        return "AGENT#{}".format(self._id)

    def act(self, observation):
        position, velocity = observation
        s = (normalize_position(position), normalize_velocity(velocity))
        return [self.policy[s]]

    def simulate(self, render=False):
        ob = self.env.reset()

        score = 0
        while True:
            if render:
                self.env.render()
                time.sleep(0.016)
            action = self.act(ob)
            ob, reward, done, _ = self.env.step(action)
            score += reward
            if done:
                break

        return score


if __name__ == '__main__':
    logger.set_level(logger.INFO)

    population = [MyAgent() for _ in range(POPULATION_SIZE)]

    while True:
        try:
            evaluations = [(p, p.simulate()) for p in population]
            evaluations.sort(reverse=True, key=lambda a: a[1])
            population = [e[0] for e in evaluations][:MAX_POPULATION_SIZE]

            best = population[0]

            print("BEST MAX", evaluations[0])

            new_population = []

            # Cruzamento
            for i in range(POPULATION_SIZE):
                if np.random.random() >= BREEDING_CHANCE:
                    continue
                parent1 = random.choice(population)
                parent2 = parent1
                while parent1 == parent2:
                    parent2 = random.choice(population)

                alpha = np.random.rand(1, 2)
                p1 = parent1.policy
                p2 = parent2.policy

                pr = {}
                for k in product(position_range(), velocity_range()):
                    a = np.random.rand()
                    pr[k] = a * p1[k] + (1 - a) * p2[k]

                child = MyAgent(policy=pr)
                new_population.append(child)

            # Mutacao
            for p in new_population:
                if np.random.random() <= MUTATION_CHANCE:
                    pr = dict(p.policy)
                    k = random.choice(list(pr.keys()))
                    pr[k] = random_power()
                    child = MyAgent(policy=pr)
                    new_population.append(child)

            population.extend(new_population)
        except KeyboardInterrupt:
            break

    best = population[0]
    print(best.policy)

    while True:
        try:
            best.simulate(True)
        except:
            break

    env.close()
