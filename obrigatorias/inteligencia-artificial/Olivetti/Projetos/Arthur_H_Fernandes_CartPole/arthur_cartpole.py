#Arthur Henrique Fernandes RA 11061816
#QLearning: pega um estado, de um sistema de estados discretos e acoes discretas, e observa as futuras recompensas de uma determinada acao para esse estado, porem descontando essa futura recompensa pois eh melhor uma recompensa agora do que no futuro
#No CarPole, temos um problema que eh o fato de o sistema ser continuo, portanto, temos a necessidade de transformar esse espaco em discreto
#A estrategia Epsilon Greedy define como agir
#O algoritmo QLearning calcula a recompensa futura esperada dentro de um dicionario e pega o seu valor maximo para escolher a melhor acao

import gym
import numpy as np 
import matplotlib.pyplot as plt 

env = gym.make('CartPole-v0')

MAXSTATES = 10**4
GAMMA = 0.9
ALPHA = 0.01

#aqui temos a funcao que procura pelo maior valor dentro do dicionario
def max_dict(d):
	max_v = float('-inf')
	for key, val in d.items():
		if val > max_v:
			max_v = val
			max_key = key
	return max_key, max_v

#aqui ocorre a transformacao do espaco continuo para discreto
def create_bins():
	# obs[0] -> cart position --- -4.8 - 4.8
	# obs[1] -> cart velocity --- -inf - inf
	# obs[2] -> pole angle    --- -41.8 - 41.8
	# obs[3] -> pole velocity --- -inf - inf
	
	bins = np.zeros((4,10))
	bins[0] = np.linspace(-4.8, 4.8, 10)
	bins[1] = np.linspace(-5, 5, 10)
	bins[2] = np.linspace(-.418, .418, 10)
	bins[3] = np.linspace(-5, 5, 10)

	return bins

#uso da funcao digitize para transformar o continuo em discreto
def assign_bins(observation, bins):
	state = np.zeros(4)
	for i in range(4):
		state[i] = np.digitize(observation[i], bins[i])
	return state

def get_state_as_string(state):
	string_state = ''.join(str(int(e)) for e in state)
	return string_state

def get_all_states_as_string():
	states = []
	for i in range(MAXSTATES):
		states.append(str(i).zfill(4))
	return states

#inicializa o dicionario
def initialize_Q():
	Q = {}

	all_states = get_all_states_as_string()
	for state in all_states:
		Q[state] = {}
		for action in range(env.action_space.n):
			Q[state][action] = 0
	return Q

def play_one_game(bins, Q, eps=0.5):
	observation = env.reset()
	done = False
	cnt = 0 # quantidade de movimentos em um episodio
	state = get_state_as_string(assign_bins(observation, bins))
	total_reward = 0

	while not done:
		cnt += 1	
		
		if np.random.uniform() < eps:
			act = env.action_space.sample() # epsilon greedy
		else:			
			act = max_dict(Q[state])[0]
		
		observation, reward, done, _ = env.step(act)

		total_reward += reward

		if done and cnt < 200:
			reward = -300

		state_new = get_state_as_string(assign_bins(observation, bins))

		a1, max_q_s1a1 = max_dict(Q[state_new])
		Q[state][act] += ALPHA*(reward + GAMMA*max_q_s1a1 - Q[state][act])
		state, act = state_new, a1					

	return total_reward, cnt

#N=10000, numero de jogos que serao jogados
def play_many_games(bins, N=10000):
	Q = initialize_Q()

	length = []
	reward = []
	for n in range(N):
		
		eps = 1.0 / np.sqrt(n+1)

		episode_reward, episode_length = play_one_game(bins, Q, eps)
		
		if n % 100 == 0:
			print(n, '%.4f' % eps, episode_reward)
		length.append(episode_length)
		reward.append(episode_reward)

	return length, reward

#cria uma array vazia, intera dentro dela, tira a media de 100 jogos e plota
def plot_running_avg(totalrewards):
	N = len(totalrewards)
	running_avg = np.empty(N)
	for t in range(N):
		running_avg[t] = np.mean(totalrewards[max(0, t-100):(t+1)])
	plt.plot(running_avg)
	plt.title("Running Average")
	plt.show()

if __name__ == '__main__':
	bins = create_bins()
	episode_lengths, episode_rewards = play_many_games(bins)

plot_running_avg(episode_rewards)
