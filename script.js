document.addEventListener('DOMContentLoaded', () => {

    // Tab Switching Functionality
    const navItems = document.querySelectorAll('.nav-item');
    const tabContents = document.querySelectorAll('.tab-content');
    const switchTabBtns = document.querySelectorAll('.switch-tab-btn');

    function activateTab(tabId) {
        // Remove active class from all tabs & nav items
        tabContents.forEach(content => content.classList.remove('active'));
        navItems.forEach(item => item.classList.remove('active'));

        // Activate selected tab content
        const targetTab = document.getElementById(tabId);
        if (targetTab) {
            targetTab.classList.add('active');
        }

        // Highlight matching nav item
        const activeNavItem = document.querySelector(`.nav-item[data-tab="${tabId}"]`);
        if (activeNavItem) {
            activeNavItem.classList.add('active');
        }

        // Scroll to top of content smoothly
        window.scrollTo({ top: 0, behavior: 'smooth' });
    }

    // Add click event to Navbar items
    navItems.forEach(item => {
        item.addEventListener('click', () => {
            const tabId = item.getAttribute('data-tab');
            if (tabId) {
                activateTab(tabId);
            }
        });
    });

    // Add click event to buttons inside pages (e.g., "Learn More", "Get in Touch")
    switchTabBtns.forEach(btn => {
        btn.addEventListener('click', () => {
            const tabId = btn.getAttribute('data-tab');
            if (tabId) {
                activateTab(tabId);
            }
        });
    });

    // Modal CV Functionality
    const modal = document.getElementById('cvModal');
    const openCvBtn = document.getElementById('openCvBtn');
    const closeBtn = document.querySelector('.close-btn');

    if (openCvBtn && modal) {
        openCvBtn.addEventListener('click', () => {
            modal.style.display = 'flex';
        });
    }

    if (closeBtn && modal) {
        closeBtn.addEventListener('click', () => {
            modal.style.display = 'none';
        });
    }

    window.addEventListener('click', (event) => {
        if (event.target === modal) {
            modal.style.display = 'none';
        }
    });

});