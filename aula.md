Algoritmo do servidor central 

- não é eficiente e não é escalavel, mas depende da aplicação.
- Quando mais aneis adicionados, maior o tempo que irá demorar.

Algoritmo de multicast

- A ideia basica é que os processos que solicitam a entrada em uma seção critica difundem seletivamente(multicast) uma mensagem de requisição e só podem entrar nela quando todos os outros processos tiverem respondido a essa mensagem.

-Precisa garatir que no maximo um processo por vez pode ser executado na seção critica.
-Se uma requisição para entrar na SC aconteceu antes de outra, então a entrada na SC é garantida nesta ordem

Se um processo solicita entrada e o estado dos outro processos é RELEASED então todos responderão imediatamente a requisição e o solicitante obtera a entrada. Se algum processo estiver no estado HELD, então esse processo não responderá as requisições até que tenha terminado com a seção critica; Portando, o solicitante não poderá entrar nesse meio tempo.
Se dois ou mais procesos solicitam a entrada ao mesmo tempo, a requisição do processo que apresentar o carimbo de tempo mais baixo será o primeiro a coletar N-1 respostas, garantindo a proxima entrada. Se o carimbo de tempo de Lamport forem iguais, serão 

Para ilustrar o algoritmo, considere uma situação envolvendo três processos, p1 , p2 e p3 , apresentada na Figura 15.5. Vamos supor que p3 não esteja interessado em entrar na seção crítica e que p1 e p2 solicitam a entrada concorrentemente. O carimbo de tempo da requisição de p1 é 41 e a de p2 é 34. Quando p3 recebe as requisições, responde imediatamente. Quando p2 recebe a requisição de p1 , verifica que sua própria requisição tem o
carimbo de tempo mais baixo e, portanto, não responde, detendo p 1 . Entretanto, p1 verifica que a requisição de p2 tem um carimbo de tempo mais baixo do que à da sua própria requisição e, portanto, responde imediatamente. Ao receber essa segunda resposta, p2 pode entrar na seção crítica. Quando p2 sair da seção crítica, responderá à requisição de p1 e, portanto, garantirá sua entrada

Vantagem:
-Seu atraso de sincronização é apenas o tempo de transmissão de uma mensagem.

------------------------------------------------------------

Algoritmo de Maekawa

Propriedades:
- Não é necessario que todos os pares concedam o acesso a seção critica
- Os processos só precisam obter permissão de subconjuntos de seus pares para entrar, desde que os subconjuntos usados por quaisquer dois processos se sobreponham.
- Podemos considerar que os processos votam uns nos outros para entrar na seção critica
- O algoritmo evita que dois processo entrem na seção critica ao mesmo, atraves do processo de intersecção de dois conjuntos de votantes
- O algoritmo permite que um processo deposite no maximo um voto entre sucessivos recebimentos de uma mensagem de liberação.
- Porque |Vi| = K?
  - Para ser imparcial todos tem os mesmo tamanhos

Funcionamento do Algoritmo:
Para obter entrada na seção critica, um processo p1 envia mensagens de requisição para todos os K membros de Vi(incluindo ele mesmo). Pi não pode entrar na seção critica até que tenha recebido todas as K mensagens de resposta. Quando um processo Pj em Vi recebe a mensagem de requisição de Pi, ele envia uma mensagem de resposta imediatamente e muda o valor do "voto" para verdadeiro, a não ser que seu estado seja HELD ou que já tenha respondido("votado") desde a ultima vez que recebeu uma mensagem de liberação.
Caso contrario, ele enfileira a mensagem de requisição (na ordem de sua chegada), mas não responde ainda. Quando um processo recebe uma mensagem de liberação, ele remove o nodo cabeça de sua fila de requisĩções pendentes(se a fila não estiver vazia) e envia uma mensagem de resposta(um "voto") em retorno a ela. Para sair da seção critica, Pi envia mensagens de liberação para todos os K membros de Vi(incluindo ele mesmo).

Desvantagem:
- propenso a impasses, pois se três processos solicitam a entrada na seção critica, então é possivel que p1 responda para si mesmo e detenha p2, que p2 responda para si mesmo e detenha p3 e que p3 responda para si mesmo e detenha p1.

Adaptação:
O algorimo pode ser adaptado de modo que se torne livre de impasses. No protocolo adaptado, os processos enfileiram as requisições pendentes na ordem acontece antes, de modo a garantir que se uma requisição para entrar na SC aconteceu antes de outra, entao a entrada na SC é garantida nessa ordem.

Comparativo com o algoritmo de Ricart e Agrawala:
O atraso de cliente é o mesmo do algoritmo de Ricart e Agrawala, mas o atraso de sincronização é pior: um tempo de viagem de ida e volta, em vez de um único tempo de transmissão de mensagem

Falhas:
O algoritmo de Maekawa pode tolerar algumas falhas de processo por colapso: se um processo falho não estiver em um conjunto votante que seja exigido, então sua falha não afetará os outros processos.


-----------------------------------------------------------------
 
Eleição baseada em anel

- Necessario para escolher qual dos processos desempenhará a função de servidor
- O primeiro que detectar que o mestre deixou de funcionar, comeca a eleição
- Processo de maior numero é o cordenador
- Termina quando chegar no proprio, faz rota inteira para verifica se processo é o maior, se for maior vira cadidanto a cordenador

Desvantagens:
- Passa duas vezes pelo anel
- Processos tem que espera toda rota

------------------------------------------------------
Algoritmo do valentão

- Permite que os processos falhem durante uma eleição, embora presuma que a distribuição de mensagens entre os processos seja confiável
- Presume que o sistema é síncrono: ele usa tempos limites para detectar
uma falha de processo
- Presume que cada processo sabe quais processos têm identificadores mais altos e que pode se comunicar com todos esses processos

--------------------------------------------------------
Capitulo 15
Pag. 646 até 653

Coordenação e acordo na comunicação em grupo


Modelo de sistema 
O sistema contém um conjunto de processos, os quais podem se comunicar com confiabilidade por meio de canais um para um. Como antes, os processos podem falhar apenas por colapso.
Os processos são membros de grupos, os quais são os destinos das mensagens enviadas com a operação de multicast. Geralmente, é util permitir que os processos sejam membtos de varios grupos simultameamente - por exemplo, para permitir que processos recebam informações de varias fontes, entrando em varios grupos. No entanto, para simplificar nossa discussão sobre as propriedades de ordenação, às vezes restringiremos os processos de modo a serem membros de no máximo um grupo por vez;
A operação multicast envia a mensagem m para todos os membros do grupo g(processos). Correspondentemente, existe uma operação deliver(m) que distribui (entrega) uma mensagem recebida por multicast para o processo que a executa.
Toda mensagem m transporta o identificador exclusivo do processo sender(m) que
a enviou e o identificador de grupo de destino exclusivo group(m). Supomos que os processos não mentem sobre a origem ou destinos das mensagens.


Multicast básico

- Garante, ao contrário do multicast IP, que um processo correto entregará a mensagem, desde que o difusor não falhe.

- Chamamos a primitiva de B-multicast e sua primitiva de entrega basica correspondente de B-deliver

- Permitimos que os processos pertençam a varios grupos, e cada mensagem é destinada a algum grupo em particular

- Uma maneira simples de implementar B-multicast é usando uma operação send de um para um confiavel, como segue:
     Para B-multicast(g,m): para cada processo p pertencente a g, send(p,m);
     Em receive(m) em p: B-deliver(m) em p.

A implementação pode usar threads para executar as operações send concorrentemente em uma tentativa de reduzir o tempo total gasto para distribuir a mensagem. Infelizmente, tal implementação é propensa a sofrer a conhecida explosão de confirmações, caso o numero de processos seja grande.
Os sinais de confirmação, enviados como parte da operação send confiável, estão sujeitos a chegar de muitos processos quase ao mesmo tempo.
Os buffers dos processos serão consumidos rapidamente e os sinais de confirmação podem ser perdidos. Portanto, ele retransmitirá a mensagem, acarretando ainda mais sinais de confirmações e mais desperdício de largura de banda de rede. Um serviço multicast básico mais prático pode ser construído, usando-se multicast IP.

