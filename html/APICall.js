const apiAddress = "http://localhost:8080/api";

const usernameInput = document.getElementById("username");
const apiCallButton = document.getElementById("apiCallButton");
const apiResponse = document.getElementById("apiResponse");

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

apiCallButton.addEventListener("click", APICall);
