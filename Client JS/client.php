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
    <div>
        <div class="clearfix">
            <div class="col-lg-12">
                <div class="chat">
                    <div class="chat-history">
                    <p class="fixed-top ml-3 mt-2" id="status">Status : Aucun</p>
                        <ul class="m-b-0">
                            <li class="clearfix">
                                <div class="message-data text-right">
                                    <span class="message-data-time">10:10 AM, Today</span>
                                </div>

                                <div class="message other-message float-right"> Hi Aiden, how are you? How is the project coming along? </div>
                            </li>

                            <li class="clearfix">
                                <div class="message-data">
                                    <span class="message-data-time">10:12 AM, Today</span>
                                </div>
                                <div class="message my-message">Are we meeting today?</div>
                            </li>

                            <li class="clearfix">
                                <div class="message-data">
                                    <span class="message-data-time">10:15 AM, Today</span>
                                </div>

                                <div class="message my-message">Project has been already finished and I have results to show you.</div>
                            </li>

                            <li class="clearfix">
                                <div class="message-data text-right">
                                    <span class="message-data-time">10:10 AM, Today</span>
                                </div>

                                <div class="message other-message float-right"> Hi Aiden, how are you? How is the project coming along? </div>
                            </li>
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