# Exercícios de Grafos

## Observações

Os arquivos estão separados em duas pastas principais, src e include, onde estão majoritariamente separados os arquivos .c e .h

### Alunos

Andre Luis Mendes Fakhoury, 4482145

David Cairuz da Silva, 10830061

Debora Buzon da Silva, 10851687

Eduardo Dias Pennone, 8937246

Giovana Daniele da Silva, 10692224

## Pavimentos de Estradas

Execução:
```
$ make fleury
$ make run
```

O grafo correspondente à estrada deve ser criado no próprio arquivo fleury.c.

## Detecção de Plágio

Execução:
```
make plagio
make run
```

Os arquivos dos dois textos correspondentes devem estar dentro da pasta cases/, com os nomes de txt1 e txt2. Para gerar esses arquivos, pode ser usado um parser (*make parser*, com o arquivo fonte respeitando a formatação do site lxcenter.)

## Caça ao Fantasma

Execução:
```
make wave
make run
```

Assim que o programa é executado, já é possível ver na tela o PacMan (amarelo) e o Fantasma (vermelho). O fantasma utiliza movimentos aleatórios, e o pacman utiliza um algoritmo guloso para chegar mais próximo do fantasma, a partir da utilização do *wavefront*.