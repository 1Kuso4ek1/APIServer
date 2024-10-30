const apiKeyAddress = "http://localhost:8080/auth";

const usernameKeyInput = document.getElementById("usernameKey");
const passwordKeyInput = document.getElementById("passwordKey");
const apiKeyInput = document.getElementById("apiKey");
const registerButton = document.getElementById("registerButton");
const getUserButton = document.getElementById("getUserButton");
const apiKeyResponse = document.getElementById("apiKeyResponse");

function Register()
{
    fetch(apiKeyAddress,
        {
            body: JSON.stringify(
            {
                name: usernameKeyInput.value,
                password: passwordKeyInput.value
            }),
            method: "POST"
        })
        .then(response => response.json())
        .then(data => {
            apiKeyResponse.innerHTML = `
                <p>API Response:</p>
                <pre>${ JSON.stringify(data, null, 2) }</pre>
            `;
        })
        .catch(error => {
            apiKeyResponse.innerHTML = `
                <p>Error fetching data:</p>
                <pre>${ error.message }</pre>
            `;
        });
}

function GetUserInfo()
{
    fetch(apiKeyAddress,
    {
        headers:
        {
            Authorization: "Bearer " + apiKeyInput.value
        },
        method: "GET"
    })
    .then(response => response.json())
    .then(data => {
        apiKeyResponse.innerHTML = `
            <p>API Response:</p>
            <pre>${ JSON.stringify(data, null, 2) }</pre>
        `;
    })
    .catch(error => {
        apiKeyResponse.innerHTML = `
            <p>Error fetching data:</p>
            <pre>${ error.message }</pre>
        `;
    });
}

registerButton.addEventListener("click", Register);
getUserButton.addEventListener("click", GetUserInfo);
