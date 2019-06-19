Algoritmo do servidor central 

- não é eficiente e não é escalavel, mas depende da aplicação.
- Quando mais aneis adicionados, maior o tempo que irá demorar.

Algoritmo de multicast

- A ideia basica é que os processos que solicitam a entrada em uma seção critica difundem seletivamente(multicast) uma mensagem de requisição e só podem entrar nela quando todos os outros processos tiverem respondido a essa mensagem.

-Precisa garatir que no maximo um processo por vez pode ser executado na seção critica.
-Se uma requisição para entrar na SC aconteceu antes de outra, então a entrada na SC é garantida nesta ordem

Se um processo solicita entrada e o estado dos outro processos é RELEASED então todos responderão imediatamente a requisição e o solicitante obtera a entrada. Se algum processo estiver no estado HELD, então esse processo não responderá as requisições até que tenha terminado com a seção critica; Portando, o solicitante não poderá entrar nesse meio tempo.

Para ilustrar o algoritmo, considere uma situação envolvendo três processos, p1 , p2 e p3 , apresentada na Figura 15.5. Vamos supor que p3 não esteja interessado em entrar na seção crítica e que p1 e p2 solicitam a entrada concorrentemente. O carimbo de tempo da requisição de p1 é 41 e a de p2 é 34. Quando p3 recebe as requisições, responde imediatamente. Quando p2 recebe a requisição de p1 , verifica que sua própria requisição tem o
carimbo de tempo mais baixo e, portanto, não responde, detendo p 1 . Entretanto, p1 verifica que a requisição de p2 tem um carimbo de tempo mais baixo do que à da sua própria requisição e, portanto, responde imediatamente. Ao receber essa segunda resposta, p2 pode entrar na seção crítica. Quando p2 sair da seção crítica, responderá à requisição de p1 e, portanto, garantirá sua entrada

Vantagem:
-Seu atraso de sincronização é apenas o tempo de transmissão de uma mensagem.