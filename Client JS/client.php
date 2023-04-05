<!DOCTYPE html>
<html lang="fr">
    <head>
        <meta charset='utf-8'>
        <meta http-equiv='X-UA-Compatible' content='IE=edge'>
        <title>Client</title>
        <meta name='viewport' content='width=device-width, initial-scale=1'>
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@4.5.0/dist/css/bootstrap.min.css" rel="stylesheet">
        <link href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet">
        <link rel="stylesheet" type="text/css" href="css/style.css">
    </head>

    <body>
        <button style="width:150px; height:40px; margin-top:40px;" class="btn btn-primary btn-disconnecting fixed-top mx-auto" id="disconnecting">Déconnexion</button>
    <div>
        <div class="clearfix">
            <div class="col-lg-12">
                <div class="chat">
                    <div class="chat-history">
                        <p class="fixed-top mt-2 text-center" id="status">Status : Aucun</p>
                        <ul class="m-b-0" id="receiveMessages">
                        </ul>
                    </div>

                    <div class="chat-message clearfix">
                    <div class="input-group fixed-bottom">
                        <div class="input-group-prepend">
                            <button type="button" class="btn btn-primary" id="sendMessage"><i class="fa fa-send"></i></button>
                        </div>
                        
                        <input type="text" class="form-control" id="saisiMessage" placeholder="Entrez le texte souhaiter ...">
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
    
        <script src="https://code.jquery.com/jquery-1.10.2.min.js"></script>
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.5.0/dist/js/bootstrap.bundle.min.js"></script>
        <script src="js/client.js"></script>
    </body>
</html>