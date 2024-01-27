# Trabalho de Programação 2: Software gerenciador de loja de roupas

## Sobre o projeto
Este projeto consiste em um sistema gerenciador de compras para uma loja de roupas fictícia, desenvolvido em linguagem C durante o meu segundo período da faculdade. O programa oferece aos usuários a capacidade de cadastrar informações sobre compras, visualizar compras específicas com base no nome do cliente e obter estatísticas pertinentes referentes a todas as compras registradas.

## Funcionalidades

1. Cadastro de compras
    * Permite cadastrar múltiplas compras de clientes, incluindo informações como nome, sexo, idade, quantidade de itens comprados e o valor total da compra.
    * Garante a integridade dos dados, exigindo que o nome do cliente tenha no mínimo 3 caracteres, o sexo seja especificado como 'f' ou 'm', a idade seja não negativa e que tanto a quantidade de itens quanto o valor total da compra sejam valores positivos maiores que zero.
    * Os dados são armazenados em um arquivo chamado "registros.txt".

2. Consulta de Informações:
    * Possibilita visualizar informações detalhadas sobre as compras de um cliente específico, informando o nome do cliente desejado.
    * Calcula e exibe a média de valores dos itens comprados por esse cliente.

3. Visualizar Dados Gerais de Todas as Compras
    * Apresenta estatísticas gerais sobre todas as compras registradas, incluindo:
        * Número de compras acima de um valor especificado.
        * Número de compras com apenas um item.
        * Número de compradores homens e mulheres, com os valores totais de compras por sexo.
        * Número total de itens vendidos.
        * Número total de compras.
        * Valor total de compras.
        * Valor médio de uma compra.
        * Informações sobre o cliente de maior nome e o cliente mais novo, incluindo detalhes de suas compras.

4. Encerrar o Programa
    * Finaliza a execução do programa.

## Execução
* O programa é executado a partir do arquivo compilado, e o usuário interage com o sistema através de um menu no console.
* Cada funcionalidade é acessada selecionando a opção correspondente no menu principal.
* Durante a execução, o usuário pode escolher voltar ao menu principal, realizar novas ações ou encerrar o programa.

## Observações
1. Este projeto é puramente didático e foi criado para fins de aprendizado.

2. O programa atualmente não suporta nomes compostos ou com sobrenomes. Cada cliente deve ser registrado com um nome simples, sem espaços extras.

3. O programa realiza verificações básicas para garantir a consistência dos dados, como o tamanho mínimo do nome, especificação correta do sexo ('f' ou 'm'), e a não negatividade da idade, quantidade de itens e valor total da compra. No entanto, verificações mais complexas, como a igualdade de dados (sexo e idade) quando os nomes são repetidos, a consideração de nomes repetidos na contagem de homens e mulheres, a identificação de múltiplos nomes com o maior número de letras, e a detecção de mais de um nome com a idade mais nova, não são realizadas no momento.

## Contribuições
Este sistema foi desenvolvido como um projeto específico, mas sugestões e contribuições são bem-vindas. Se você encontrar algum problema ou tiver ideias para melhorias, sinta-se à vontade para abrir uma questão ou enviar uma solicitação de pull.

## Licença
Este projeto é licenciado sob a [Licença MIT](./LICENSE). Consulte o arquivo [LICENSE](./LICENSE) para obter mais informações.