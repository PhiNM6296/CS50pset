// Function to navigate to the specified result page
function navigateToResultPage(targetUrl) {
    // Redirect the user to the specified result page
    window.location.href = targetUrl;
}
document.getElementById('searchInput').addEventListener('keypress', function(event) {
    if (event.key === 'Enter') {
        var targetUrl = 'video.html';
        // Redirect the user to the result page
        navigateToResultPage(targetUrl);
    }
});

// Function to set the theme (light/dark) and persist the user's preference
function setTheme(theme) {
    document.documentElement.setAttribute('data-theme', theme);
    localStorage.setItem('theme', theme);
    updateThemeIcon(theme); // Update the theme icon after setting the theme
}

// Function to retrieve the user's preferred theme from localStorage
function getTheme() {
    return localStorage.getItem('theme') || 'light'; // Default to light mode if no preference is found
}

// Function to update the theme icon based on the selected theme
function updateThemeIcon(theme) {
    const iconElement = document.getElementById('themeIcon');
    if (theme === 'dark') {
        iconElement.classList.remove('fa-sun'); // Remove sun icon
        iconElement.classList.add('fa-moon'); // Add moon icon
        iconElement.style.color = '#ffffff'; // Set icon color to white
    } else {
        iconElement.classList.remove('fa-moon'); // Remove moon icon
        iconElement.classList.add('fa-sun'); // Add sun icon
        iconElement.style.color = '#000000'; // Set icon color to black
    }
}

// Apply the user's preferred theme on page load
document.addEventListener('DOMContentLoaded', function() {
    const currentTheme = getTheme();
    setTheme(currentTheme);
});

// Function to navigate to the specified result page
function navigateToResultPage(targetUrl) {
    // Redirect the user to the specified result page
    window.location.href = targetUrl;
}

// Handle theme change when dropdown option is clicked
function setThemeFromDropdown(theme) {
    setTheme(theme);
}
