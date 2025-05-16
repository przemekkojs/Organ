const header = document.getElementById('header');

header.innerHTML = `
<nav class="navbar navbar-expand-lg navbar-light bg-light border-bottom">
    <div class="container-fluid">
        <a class="navbar-brand d-flex align-items-center" href="#">
            <img src="img/logo.jpg" alt="Logo" width="40" height="40" class="me-2">
            <span>Organ</span>
        </a>
        <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNavDropdown">
            <span class="navbar-toggler-icon"></span>
        </button>
        <div class="collapse navbar-collapse" id="navbarNavDropdown">
            <ul class="navbar-nav ms-auto">
                <li class="nav-item">
                    <a class="nav-link" href="#">Strona główna</a>
                </li>
                <li class="nav-item dropdown">
                    <a class="nav-link dropdown-toggle" href="#" id="oProjekcieDropdown" role="button" data-bs-toggle="dropdown">
                        O projekcie
                    </a>
                    <ul class="dropdown-menu" aria-labelledby="oProjekcieDropdown">
                        <li><a class="dropdown-item" href="#">Opis</a></li>
                        <li><a class="dropdown-item" href="#">Dokumentacja</a></li>
                        <li><a class="dropdown-item" href="#">GitHub</a></li>
                    </ul>
                </li>
                <li class="nav-item dropdown">
                    <a class="nav-link dropdown-toggle" href="#" id="pomocDropdown" role="button" data-bs-toggle="dropdown">
                        Pomoc
                    </a>
                    <ul class="dropdown-menu" aria-labelledby="pomocDropdown">
                        <li><a class="dropdown-item" href="#">Kontakt</a></li>
                    </ul>
                </li>
            </ul>
        </div>
    </div>
</nav>
`;