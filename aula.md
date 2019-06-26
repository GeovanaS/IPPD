Bônus ganho: 0.5(apresentação) + 0.2(perguntas) + 0.1(pergunta) 

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
Os buffers dos processos serão consumidos rapidamente e os sinais de confirmação podem ser perdidos. Portanto, ele retransmitirá a mensagem, acarretando ainda mais sinais de confirmações e mais desperdício de largura de banda de rede. Um serviço multicast básico mais prático pode ser construído, usando-se multicast IP

Multicast Confiável

Seguindo Hadzilacos e Toueg [1994] e Chandra e Toueg [1996], definiremos o multicast confiável, com as operações correspondentes R-multicast e R-deliver (o R é de “reliable”, que é “confiável” em inglês). Claramente, propriedades análogas à integridade e à validade são altamente desejáveis na distribuição por multicast confiável, mas acrescentamos outra: o requisito de que todos os processos corretos do grupo devem receber uma mensagem, caso qualquer um deles receba. É importante perceber que essa não é uma propriedade do algoritmo B-multicast, que é baseado em uma operação send de um para um confiável. O remetente pode falhar em qualquer ponto, enquanto B-multicast prossegue; portanto, alguns processos podem distribuir uma mensagem, enquanto outros não


O multicast confiável é aquele que satisfaz as seguintes propriedades:

- Integridade: um processo correto p entrega uma mensagem m no máximo uma
vez. Além disso, p ∈ group(m) e m foi fornecida para uma operação multicast
por sender(m). (Assim como acontece com a comunicação de um para um, as
mensagens sempre podem ser diferenciadas por um número de sequência relativo aos seus remetentes

- Validade: se um processo correto executa um multicast da mensagem m, então, ele distribuirá m.

- Acordo: se um processo correto entrega a mensagem m, então todos os outros processos corretos em group(m) distribuirão m.

A propriedade da integridade é análoga à da comunicação um para um confiável. A propriedade da validade garante a subsistência do remetente. Essa propriedade pode parecer incomum, pois é assimétrica (ela menciona apenas um processo em particular). No entanto, observe que, juntos, a validade e o acordo significam um requisito de subsistência global: se um processo (o remetente) distribuir uma mensagem m, então, como os processos corretos concordam com o conjunto de mensagens que distribuem, segue-se que m finalmente será entregue para todos os membros corretos do grupo.
A vantagem de expressar a condição de validade em termos de autoentrega é a
simplicidade. O que necessitamos é que a mensagem seja entregue por algum membro
correto do grupo

A condição do acordo está relacionada à atomicidade, a propriedade do “tudo ou
nada”, aplicada à entrega de mensagens para um grupo. Se um processo que envia por multicast uma mensagem falha antes de tê-la entregue, então é possível que a mensagem não seja entregue para nenhum processo do grupo; mas se ela for entregue para algum processo correto, então todos os outros processos corretos a entregarão. Muitos artigos na literatura usam o termo “atômico” para incluir uma condição de ordenação total; definiremos isso em breve.

Garantias:
 As do multicast básico
 Mais:
     se um processo do grupo g recebe, todos devem receber
 No multicast básico (anterior) não há controle se alguém não recebe
     Ocorre se emissor falha durante envio

Implementação de multicast confiável por meio de B-multicast 
• A Figura 15.9 fornece um algoritmo de multicast confiável, com primitivas R-multicast e R-deliver, o qual permite aos processos pertencerem a vários grupos fechados simultaneamente. Para enviar uma mensagem com R-multicast, um processo a envia com B-multicast para os processos no grupo de destino (incluindo ele mesmo). Quando a mensagem é entregue com B-deliver, o destinatário, por sua vez, a entrega com B-multicast para o grupo (se ele não for o remetente original) e depois a entrega com R-deliver. Como uma mensagem pode chegar mais de uma vez, as duplicatas são detectadas e não enviadas.
Esse algoritmo claramente satisfaz a validade, pois um processo correto entregará a mensagem para si mesmo com B-deliver. Pela propriedade da integridade dos canais de comunicação subjacente usados em B-multicast, o algoritmo também satisfaz a propriedade da integridade.
Esse algoritmo claramente satisfaz a validade, pois um processo correto entregará a mensagem para si mesmo com B-deliver. Pela propriedade da integridade dos canais de comunicação subjacente usados em B-multicast, o algoritmo também satisfaz a propriedade da integridade.

O acordo resulta do fato de que todo processo correto envia a mensagem com B-
-multicast para os outros processos, após tê-la entregue com B-deliver. Se um processo
correto não entregar a mensagem com R-deliver, então só pode ser porque ele nunca o
fez com B-deliver. Isso, por sua vez, só pode ser porque nenhum outro processo correto a
entregou com B-deliver; portanto, nenhum a enviará com R-deliver.
O algoritmo de multicast confiável que descrevemos é correto em um sistema assíncrono, pois não fizemos suposições de temporização. Contudo, o algoritmo é ineficiente para propósitos práticos. Cada mensagem é enviada |g| vezes para cada processo

O algoritmo de multicast confiável que descrevemos é correto em um sistema assíncrono, pois não fizemos suposições de temporização. Contudo, o algoritmo é ineficiente para propósitos práticos. Cada mensagem é enviada |g| vezes para cada processo

Multicast confiável por meio de multicast IP

• Uma realização alternativa de R-multicast é usar uma combinação multicast IP, confirmações “de carona” (isto é, confirmações anexadas em outras mensagens) e confirmações negativas. Esse protocolo R-multicast
é baseado na observação de que a comunicação por multicast IP é frequentemente bem-sucedida. No protocolo, os processos não enviam mensagens de confirmação separadas;
em vez disso, elas colocam as confirmações “de carona” das mensagens que enviam para o grupo. Os processos enviam uma mensagem de resposta separada apenas quando detectam que perderam uma mensagem. Uma resposta indicando a ausência de uma mensagem esperada é conhecida como confirmação negativa

A descrição presume que os grupos são fechados. Cada processo p mantém um número de sequência Sgp para cada grupo g ao qual pertence. O número de sequência inicialmente é zero. Cada processo também grava R gq, o número de sequência da última mensagem que recebeu do processo q enviada para o grupo g.
Para p enviar uma mensagem com R-multicast para o grupo g, ele coloca o valor Sgp e a confirmação “de carona” na mensagem, na forma <q, R gq>. Uma confirmação informa, para um remetente q, o número de sequência da mensagem mais recente de q, destinada a g, que p entregou desde que fez um multicast. Então, o emissor p envia a mensagem por multicast IP para g, com seus valores “de carona”, e incrementa Sgppor u

Os valores “de carona” em uma mensagem multicast permitem que os destinatá-
rios saibam sobre as mensagens que não receberam. Um processo entrega uma mensagem com R-deliver, destinada a g, contendo o número de sequência S de p, se e somente se S = R^q g + 1, e incrementa R^gq por um, imediatamente após a distribuição. Se uma mensagem recebida tem S ≤ R gq, então r enviou a mensagem antes e a descarta. Se S > R q g + 1 ou se R > R gq com uma confirmação incluída <q, R>, então existe uma ou mais mensagens ainda não recebidas (e que provavelmente foram eliminadas, no primeiro
caso). Ele mantém toda mensagem para a qual S > R gq + 1, em uma fila de espera (Figura
15.10) – tais filas são frequentemente usadas para satisfazer garantias de distribuição de
mensagem. Ele solicita as mensagens ausentes enviando confirmações negativas para o
remetente original, ou para um processo q a partir do qual recebeu uma confirmação <q,
R q g>, com R gq não menor do que o número de sequência exigido.
 fila de espera não é rigorosamente necessária para a confiabilidade, mas simplifica o protocolo, permitindo-nos usar números de sequência para representar conjuntos
de mensagens enviadas. Ela também nos fornece uma garantia da ordem de envio (veja
a Seção 15.4.3).
A propriedade da integridade resulta da detecção de duplicatas e das propriedades
subjacentes do multicast IP (que usa somas de verificação para eliminar mensagens corrompidas). A propriedade da validade vale porque o multicast IP tem essa propriedade.
Para o acordo, exigimos primeiro que um processo sempre possa detectar mensagens
ausentes. Isso, por sua vez, significa que ele sempre receberá mais uma mensagem que
permita detectar a omissão. Conforme o protocolo simplificado, garantimos a detecção
de mensagens ausentes apenas no caso em que processos corretos enviam mensagens
por multicast, indefinidamente. Segundo, a propriedade do acordo exige que sempre haja
uma cópia disponível de toda mensagem necessária para um processo que não a recebeu.
Portanto, presumimos que os processos mantêm indefinidamente as cópias das mensagens que enviaram – nesse protocolo simplificado.
Nenhuma das suposições que fizemos para garantir o acordo é prática (veja o Exercício 15.15). Entretanto, o acordo é tratado praticamente em todos os protocolos dos quais
o nosso é derivado: o protocolo Psync [Peterson et al. 1989], o protocolo Trans [Melliar-
-Smith et al. 1990] e o protocolo de multicast confiável escalável [Floyd et al. 1997]. Os
protocolos Psync e Trans também fornecem outras garantias de ordenação de entrega.

ropriedades uniformes • A definição de acordo dada anteriormente se refere apenas ao
comportamento de processos corretos – processos que nunca falham. Considere o que
aconteceria no algoritmo da Figura 15.9 se um processo não fosse correto e falhasse após
ter entregue uma mensagem com R-deliver. Como todo processo que entrega mensagem
com R-deliver deve primeiro enviá-la com B-multicast, segue-se que todos os processos
corretos terminarão por entregar a mensagem.
Toda propriedade que vale, sejam os processos corretos ou não, é chamada de propriedade uniforme. Definimos o acordo uniforme como segue:
Acordo uniforme: se um processo, correto ou falho, entregar uma mensagem m,
então todos os processos corretos em group(m) entregarão.
O acordo uniforme permite que um processo falhe após ter enviado uma mensagem,
enquanto ainda garante que todos os processos corretos entregarão a mensagem. Argumentamos que o algoritmo da Figura 15.9 satisfaz essa propriedade, que é mais forte do
que a propriedade do acordo não uniforme, definida anteriormente.
O acordo uniforme é útil em aplicações em que um processo pode executar uma
ação que produz uma inconsistência observável antes de falhar. Por exemplo, considere
que os processos são servidores gerenciando cópias de uma conta bancária, e que as atualizações na conta são enviadas para o grupo de servidores usando multicast confiável.
Se o multicast não satisfizer o acordo uniforme, então um cliente que acesse um servidor
imediatamente antes dele falhar poderá observar uma atualização que nenhum outro servidor processará.
É interessante notar que, se invertermos as linhas “R-deliver m” e “if (q ≠ p) then
B-multicast(g, m); end if” na Figura 15.9, o algoritmo resultante não satisfará o acordo
uniforme.
Assim como existe uma versão uniforme do acordo, também existem versões uniformes de qualquer propriedade de multicast, incluindo validade e integridade e as propriedades de ordenação que iremos defini




