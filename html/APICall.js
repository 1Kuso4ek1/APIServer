const apiAddress = "http://localhost:8080/api";
const apiKeyAddress = "http://localhost:8080/auth";

const usernameInput = document.getElementById("username");
const apiCallButton = document.getElementById("apiCallButton");
const apiResponse = document.getElementById("apiResponse");

const usernameKeyInput = document.getElementById("usernameKey");
const apiKeyInput = document.getElementById("apiKey");
const registerButton = document.getElementById("registerButton");
const getUserButton = document.getElementById("getUserButton");
const apiKeyResponse = document.getElementById("apiKeyResponse");

function APICall()
{
    fetch(apiAddress + "?name=" + usernameInput.value)
        .then(response => response.json())
        .then(data => {
            apiResponse.innerHTML = `
                <p>API Response:</p>
                <pre>${ JSON.stringify(data, null, 2) }</pre>
            `;
        })
        .catch(error => {
            apiResponse.innerHTML = `
                <p>Error fetching data:</p>
                <pre>${ error.message }</pre>
            `;
        });
}

function Register()
{
    fetch(apiKeyAddress + "?user=" + usernameKeyInput.value, { method: "POST" })
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

apiCallButton.addEventListener("click", APICall);
registerButton.addEventListener("click", Register);
getUserButton.addEventListener("click", GetUserInfo);
